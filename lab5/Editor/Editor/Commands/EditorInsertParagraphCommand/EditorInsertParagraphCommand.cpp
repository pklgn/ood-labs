#include "../../../pch.h"
#include "EditorInsertParagraphCommand.h"

EditorInsertParagraphCommand::EditorInsertParagraphCommand(std::istream& input, HTMLDocument& document)
	: m_document(document)
	, m_input(input)
{
}

void EditorInsertParagraphCommand::Execute()
{
	std::string text;
	std::getline(m_input, text);

	if (m_input.fail())
	{
		throw std::runtime_error("Unexpected input stream content was found");
	}

	size_t position;
	m_input >> position;

	if (m_input.fail())
	{
		position = m_document.GetItemsCount();
	}

	m_document.InsertParagraph(text, position);
}
