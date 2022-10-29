#pragma once
#include <memory>

#include "../Image/IImage.h"
#include "../Paragraph/IParagraph.h"

/*
Неизменяемый элемент документа
*/
class ConstDocumentItem
{
public:
	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const;

	virtual ~ConstDocumentItem() = default;
};
