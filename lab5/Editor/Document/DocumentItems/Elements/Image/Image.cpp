#include "../../../../pch.h"
#include "Image.h"

Image::Image(size_t width, size_t height, Path path)
	: m_width(width)
	, m_height(height)
	, m_path(path)
{
}

Path Image::GetPath() const
{
	return m_path;
}

size_t Image::GetWidth() const
{
	return m_width;
}

size_t Image::GetHeight() const
{
	return m_height;
}

void Image::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}
