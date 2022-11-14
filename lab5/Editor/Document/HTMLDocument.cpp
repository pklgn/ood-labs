#include "../pch.h"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Commands/DeleteItemCommand.h"
#include "Commands/InsertImageCommand.h"
#include "Commands/InsertParagraphCommand.h"
#include "Commands/SetTitleCommand.h"
#include "Commands/ReplaceTextCommand.h"
#include "Commands/ResizeImageCommand.h"
#include "DocumentItems/Elements/Image/Image.h"
#include "DocumentItems/Elements/Paragraph/Paragraph.h"
#include "HTMLDocument.h"
#include "../common/StringCommon.h"

const std::string HTML_DOCUMENT_FILENAME_PREFIX = "Untitled";
const auto PLATFORM_SEPARATOR = std::filesystem::path::preferred_separator;

namespace fs = std::filesystem;

std::string GetCurrentDateTimeString();

HTMLDocument::HTMLDocument()
	: m_title(HTML_DOCUMENT_FILENAME_PREFIX + GetCurrentDateTimeString())
	, m_saver(*this)
{
	SetSavePath(fs::current_path().string());
}

std::shared_ptr<IParagraph> HTMLDocument::InsertParagraph(const std::string& text, std::optional<size_t> position)
{
	auto insertPosition = ValidatePosition(position);

	auto paragraphPtr = std::make_shared<Paragraph>(text);

	m_history.AddAndExecuteCommand(std::make_unique<InsertParagraphCommand>(m_items, paragraphPtr, insertPosition));

	return paragraphPtr;
}

std::shared_ptr<IImage> HTMLDocument::InsertImage(const Path& path, size_t width, size_t height, std::optional<size_t> position)
{
	auto insertPosition = ValidatePosition(position);
	auto imagePtr = std::make_shared<Image>(width, height, path);

	m_history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(m_items, imagePtr, insertPosition));

	return imagePtr;
}

size_t HTMLDocument::GetItemsCount() const
{
	return m_items.size();
}

ConstDocumentItem HTMLDocument::GetItem(size_t index) const
{
	if (m_items.size() <= index)
	{
		throw std::out_of_range("Item index is out of range");
	}

	return m_items.at(index);
}

DocumentItem HTMLDocument::GetItem(size_t index)
{
	if (m_items.size() <= index)
	{
		throw std::out_of_range("Item index is out of range");
	}

	return m_items.at(index);
}

void HTMLDocument::DeleteItem(size_t index)
{
	if (m_items.size() <= index)
	{
		throw std::out_of_range("Index is out of range");
	}

	m_history.AddAndExecuteCommand(std::make_unique<DeleteItemCommand>(m_items, index));
}

std::string HTMLDocument::GetTitle() const
{
	return m_title;
}

void HTMLDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(m_title, title));
}

bool HTMLDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void HTMLDocument::Undo()
{
	m_history.Undo();
}

bool HTMLDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void HTMLDocument::Redo()
{
	m_history.Redo();
}

void HTMLDocument::Save(const Path& path) const
{
	m_saver.Save(path);
}

void HTMLDocument::SetSavePath(const Path& path)
{
	fs::path fsPath = path;
	if (!fsPath.empty() && fsPath.generic_string().back() != PLATFORM_SEPARATOR)
	{
		fsPath += PLATFORM_SEPARATOR;
	}

	m_savePath = fsPath.string();
}

void HTMLDocument::ReplaceText(size_t index, const std::string& newText)
{
	auto item = GetItem(index);
	auto paragraph = item.GetParagraph();
	if (paragraph == nullptr)
	{
		throw std::runtime_error("Couldn't replace text for non-paragraph document item");
	}

	m_history.AddAndExecuteCommand(std::make_unique<ReplaceTextCommand>(paragraph, newText));
}

void HTMLDocument::ResizeImage(size_t index, size_t width, size_t height)
{
	auto item = GetItem(index);
	auto image = item.GetImage();
	if (image == nullptr)
	{
		throw std::runtime_error("Couldn't resize non-image document item");
	}

	m_history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(image, width, height));
}

size_t HTMLDocument::ValidatePosition(const std::optional<size_t>& position)
{
	if (m_items.size() < position)
	{
		throw std::invalid_argument("Position argument must not exceed the number of elements in the document");
	}

	return position.value_or(m_items.size());
}
