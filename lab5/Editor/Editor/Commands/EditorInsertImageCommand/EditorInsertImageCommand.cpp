#include "../../../pch.h"
#include "EditorInsertImageCommand.h"

EditorInsertImageCommand::EditorInsertImageCommand(std::istream& input, HTMLDocument& document)
	: m_document(document)
	, m_input(input)
{
}

void EditorInsertImageCommand::Execute()
{
	std::string path;
	std::getline(m_input, path);

	if (m_input.fail())
	{
		throw std::runtime_error("Unexpected input stream content was found");
	}

	size_t width;
	size_t height;
	m_input >> width >> height;

	size_t position;
	m_input >> position;

	if (m_input.fail())
	{
		position = m_document.GetItemsCount();
	}

	m_document.InsertImage(path, width, height, position);
}
