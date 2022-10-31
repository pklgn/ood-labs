#pragma once
#include "ConstDocumentItem.h"

/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class DocumentItem : public ConstDocumentItem
{
public:
	DocumentItem(std::shared_ptr<IBaseDocumentItem>);
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();
};
