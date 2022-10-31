#include "../../../pch.h"
#include "EditorDeleteItemCommand.h"

EditorDeleteItemCommand::EditorDeleteItemCommand(std::istream& input, HTMLDocument& document)
	: m_document(document)
	, m_input(input)
{
}

void EditorDeleteItemCommand::Execute()
{
	size_t index;
	m_input >> index;

	m_document.DeleteItem(index);
}
