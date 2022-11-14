#include "../../pch.h"
#include "DeleteItemCommand.h"

namespace fs = std::filesystem;

DeleteItemCommand::DeleteItemCommand(std::vector<DocumentItem>& items, size_t position)
	: m_items(items)
	, m_position(position)
	, m_documentItem(m_items.at(m_position))
{
	if (items.size() <= m_position)
	{
		throw std::out_of_range("Index out of range");
	}
}

DeleteItemCommand::~DeleteItemCommand()
{
	auto imagePtr = m_documentItem.GetImage();
	if (WasExecuted() && imagePtr != nullptr)
	{
		fs::path removePath = fs::current_path();
		removePath += fs::path::preferred_separator;
		removePath += imagePtr->GetPath();
		fs::remove(removePath);
	}
}

void DeleteItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_position);
}

void DeleteItemCommand::DoUnexecute()
{
	m_items.insert(m_items.begin(), m_documentItem);
}
