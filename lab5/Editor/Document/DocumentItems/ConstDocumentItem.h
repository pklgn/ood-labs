#pragma once
#include <memory>

#include "Elements/IElement.h"
#include "Elements/Image/IImage.h"
#include "Elements/Paragraph/IParagraph.h"

/*
Неизменяемый элемент документа
*/
class ConstDocumentItem
{
public:
	ConstDocumentItem(std::shared_ptr<IElement>);
	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~ConstDocumentItem() = default;


protected:
	std::shared_ptr<IElement> m_item;
};
