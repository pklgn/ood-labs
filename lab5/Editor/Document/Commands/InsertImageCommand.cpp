#include "../../pch.h"
#include "InsertImageCommand.h"

namespace fs = std::filesystem;

InsertImageCommand::InsertImageCommand(std::vector<DocumentItem>& items, const std::shared_ptr<IImage>& imagePtr, size_t position)
	: m_items(items)
	, m_imagePtr(imagePtr)
	, m_position(position)
{
}

InsertImageCommand::~InsertImageCommand()
{
	fs::remove(fs::current_path().string() + m_imagePtr->GetPath());
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


