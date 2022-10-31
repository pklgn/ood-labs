#include "../../pch.h"
#include "InsertImageCommand.h"

InsertImageCommand::InsertImageCommand(std::vector<DocumentItem>& items, const std::shared_ptr<IImage>& imagePtr, size_t position, const Path& path)
	: m_items(items)
	, m_imagePtr(imagePtr)
	, m_position(position)
	, m_path(path)
{
}

InsertImageCommand::~InsertImageCommand()
{
	remove(m_path.c_str());
}

void InsertImageCommand::DoExecute()
{
	if (m_position == m_items.size())
	{
		m_items.push_back(DocumentItem(m_imagePtr));
	}
	else
	{
		m_items.insert(m_items.begin() + m_position, DocumentItem(m_imagePtr));
	}
}

void InsertImageCommand::DoUnexecute()
{
	m_items.erase(m_items.begin() + m_position);
}


