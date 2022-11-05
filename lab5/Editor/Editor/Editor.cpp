#include "../pch.h"
#include "Editor.h"

Editor::Editor(std::istream& input, std::ostream& output)
	: m_menu(input, output)
	, m_input(input)
	, m_output(output)
{
	m_menu.AddItem("insert-paragraph",
		"Inserting specified paragraph with a given position",
		[this]() { InsertParagraph(); });

	m_menu.AddItem("insert-image",
		"Inserting specified image with a given position and size",
		[this]() { InsertImage(); });

	m_menu.AddItem("set-title",
		"Set a new title for the document",
		[this]() { SetTitle(); });

	m_menu.AddItem("list",
		"Show document items list",
		[this]() { List(); });

	m_menu.AddItem("replace-text",
		"Replaces text in a paragraph at a specified position in the document",
		[this]() { ReplaceText(); });

	m_menu.AddItem("resize-image",
		"Changes the size of the image at a specified position in the document",
		[this]() { ResizeImage(); });

	m_menu.AddItem("delete-item",
		"Deletes the document item in the specified position",
		[this]() { DeleteItem(); });

	m_menu.AddItem("help",
		"Displays help about available editing commands and their arguments",
		[this]() { Help(); });

	m_menu.AddItem("undo",
		"Cancels the effect of a previously entered editing command, returning the document to its previous state",
		[this]() { Undo(); });

	m_menu.AddItem("redo",
		"Executes a previously canceled editing command, returning the document to the state, undoes the Undo command",
		[this]() { Redo(); });

	m_menu.AddItem("save",
		"Saves the current state of the document in an html file with images",
		[this]() { Save(); });

	m_menu.AddItem("exit",
		"Exit from app",
		[this]() { Exit(); });
}

//TODO: убрать команды и заменить на std::function(void)

void Editor::StartEditing()
{
	m_menu.ShowInstructions();

	m_menu.Run();
}

void Editor::InsertParagraph()
{
	std::string text;
	std::getline(m_input, text);

	if (m_input.fail())
	{
		throw std::runtime_error("Paragraph text was expected");
	}

	size_t position = ReadInsertPosition();

	m_document.InsertParagraph(text, position);
}

void Editor::InsertImage()
{
	std::string path;
	std::getline(m_input, path);
	if (m_input.fail())
	{
		throw std::runtime_error("Image path was expected");
	}

	size_t width;
	size_t height;
	m_input >> width >> height;
	if (m_input.fail())
	{
		throw std::runtime_error("Couldn't resolve image size");
	}

	size_t position = ReadInsertPosition();

	m_document.InsertImage(path, width, height, position);
}

void Editor::SetTitle()
{
	std::string title;
	std::getline(m_input, title);

	if (m_input.fail())
	{
		throw std::runtime_error("Title was expected");
	}

	m_document.SetTitle(title);
}

void Editor::List() const
{
	auto itemsCount = m_document.GetItemsCount();

	m_output << "Title: "
			 << m_document.GetTitle() << std::endl;

	for (auto itemIndex = 0; itemIndex < itemsCount; ++itemIndex)
	{
		auto item = m_document.GetItem(itemIndex);
		auto imagePtr = item.GetImage();
		auto paragraphPtr = item.GetParagraph();
		if (imagePtr != nullptr)
		{
			m_output << itemIndex << ". "
					 << "Image: "
					 << imagePtr->GetWidth() << " "
					 << imagePtr->GetHeight() << " "
					 << imagePtr->GetPath() << std::endl;
		}
		else if (paragraphPtr != nullptr)
		{
			m_output << itemIndex << ". "
					 << "Paragraph: "
					 << paragraphPtr->GetText() << std::endl;
		}
	}
}

void Editor::ReplaceText()
{
	size_t position;
	m_input >> position;
	if (m_input.fail())
	{
		throw std::runtime_error("Replace position was expected");
	}

	std::string text;
	std::getline(m_input, text);
	if (m_input.fail())
	{
		throw std::runtime_error("Paragraph text was expected");
	}

	auto item = m_document.GetItem(position);
	auto paragraph = item.GetParagraph();
	if (paragraph == nullptr)
	{
		throw std::runtime_error("Couldn't replace text for non-paragraph document item");
	}

	paragraph->SetText(text);
}

void Editor::ResizeImage()
{
	size_t position;
	m_input >> position;
	if (m_input.fail())
	{
		throw std::runtime_error("Resize position was expected");
	}

	size_t width;
	size_t height;
	m_input >> width >> height;
	if (m_input.fail())
	{
		throw std::runtime_error("New values for width and height were expected");
	}

	auto item = m_document.GetItem(position);
	auto image = item.GetImage();
	if (image == nullptr)
	{
		throw std::runtime_error("Couldn't resize a non-image document item");
	}

	image->Resize(width, height);
}

void Editor::DeleteItem()
{
	size_t position;
	m_input >> position;
	if (m_input.fail())
	{
		throw std::runtime_error("Delete position was expected");
	}

	m_document.DeleteItem(position);
}

void Editor::Help() const
{
	m_menu.ShowInstructions();
}

void Editor::Undo()
{
	if (!m_document.CanUndo())
	{
		m_output << "Can't perform undo operation\n";

		return;
	}

	m_document.Undo();
}

void Editor::Redo()
{
	if (!m_document.CanRedo())
	{
		m_output << "Can't perform redo operation\n";

		return;
	}

	m_document.Redo();
}

void Editor::Save() const
{
	m_document.Save();
}

void Editor::Exit()
{
	m_menu.Exit();
}

size_t Editor::ReadInsertPosition()
{
	size_t position;
	m_input >> position;

	if (m_input.fail())
	{
		m_output << "Couldn't read insert position\n"
					"Assumed inserting at the end of the document\n";

		position = m_document.GetItemsCount();
	}

	return position;
}
