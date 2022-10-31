#pragma once
#include <string>

#include "../DocumentItems/IBaseDocumentItem.h"

using Path = std::string;

/*
Изображение
*/
class IImage : public IBaseDocumentItem
{
public:
	// Возвращает путь относительно каталога документа
	virtual Path GetPath() const = 0;

	// Ширина изображения в пикселях
	virtual size_t GetWidth() const = 0;
	// Высота изображения в пикселях
	virtual size_t GetHeight() const = 0;

	// Изменяет размер изображения
	virtual void Resize(int width, int height) = 0;

	//virtual ~IImage() = default;
};
