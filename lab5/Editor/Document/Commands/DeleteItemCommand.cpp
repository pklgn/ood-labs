#include "../../pch.h"
#include "DeleteItemCommand.h"

DeleteItemCommand::DeleteItemCommand(std::vector<DocumentItem>& items, size_t position)
	: m_items(items)
	, m_position(position)
	, m_documentItem(m_items.at(m_position))
{
}

void DeleteItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_position);
}

void DeleteItemCommand::DoUnexecute()
{
	m_items.insert(m_items.begin(), m_documentItem);
}
