#include "../../pch.h"
#include "DocumentItem.h"

DocumentItem::DocumentItem(std::shared_ptr<IElement> item)
	: ConstDocumentItem(item)
{
}

std::shared_ptr<IImage> DocumentItem::GetImage()
{
	return std::dynamic_pointer_cast<IImage>(m_item);
}

std::shared_ptr<IParagraph> DocumentItem::GetParagraph()
{
	return std::dynamic_pointer_cast<IParagraph>(m_item);
}
