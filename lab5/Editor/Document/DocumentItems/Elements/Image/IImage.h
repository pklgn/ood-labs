#pragma once
#include <string>

#include "../IElement.h"

using Path = std::string;

/*
Изображение
*/
class IImage : public IElement
{
public:
	// Возвращает путь относительно каталога документа
	virtual Path GetPath() const = 0;

	// Ширина изображения в пикселях
	virtual size_t GetWidth() const = 0;
	// Высота изображения в пикселях
	virtual size_t GetHeight() const = 0;

	// Изменяет размер изображения
	virtual void Resize(size_t width, size_t height) = 0;

	virtual void SetPath(const Path&) = 0;
};
