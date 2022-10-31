#include "../../pch.h"
#include "ConstDocumentItem.h"

ConstDocumentItem::ConstDocumentItem(std::shared_ptr<IBaseDocumentItem> item)
	: m_item(item)
{
}

std::shared_ptr<const IImage> ConstDocumentItem::GetImage() const
{
	return std::dynamic_pointer_cast<const IImage>(m_item);
}

std::shared_ptr<const IParagraph> ConstDocumentItem::GetParagraph() const
{
	return std::dynamic_pointer_cast<const IParagraph>(m_item);
}
