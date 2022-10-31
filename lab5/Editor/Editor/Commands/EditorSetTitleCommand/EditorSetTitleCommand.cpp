#include "../../../pch.h"
#include "EditorSetTitleCommand.h"

EditorSetTitleCommand::EditorSetTitleCommand(std::istream& input, HTMLDocument& document)
	: m_document(document)
	, m_input(input)
{
}

void EditorSetTitleCommand::Execute()
{
	std::string title;
	std::getline(m_input, title);

	if (m_input.fail())
	{
		throw std::runtime_error("Unexpected input stream content was found");
	}

	m_document.SetTitle(title);
}
