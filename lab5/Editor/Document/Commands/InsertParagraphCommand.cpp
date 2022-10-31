#include "../../pch.h"
#include "InsertParagraphCommand.h"


InsertParagraphCommand::InsertParagraphCommand(std::vector<DocumentItem>& items, const std::shared_ptr<IParagraph>& paragraphPtr, size_t position)
	: m_items(items)
	, m_paragraphPtr(paragraphPtr)
	, m_position(position)
{
}

void InsertParagraphCommand::DoExecute()
{
	if (m_position == m_items.size())
	{
		m_items.push_back(DocumentItem(m_paragraphPtr));
	}
	else
	{
		m_items.insert(m_items.begin() + m_position, DocumentItem(m_paragraphPtr));
	}
}

void InsertParagraphCommand::DoUnexecute()
{
	m_items.erase(m_items.begin() + m_position);
}
