#include "../../../../pch.h"
#include "Image.h"

constexpr size_t MIN_DIMENSION_SIZE = 1;
constexpr size_t MAX_DIMENSION_SIZE = 10000;

Image::Image(size_t width, size_t height, Path path)
	: m_width(width)
	, m_height(height)
	, m_path(path)
{
	ValidateImage();
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

void Image::Resize(size_t width, size_t height)
{
	m_width = width;
	m_height = height;
}

void Image::ValidateImage()
{
	if ((m_width < MIN_DIMENSION_SIZE || MAX_DIMENSION_SIZE < m_width) ||
		(m_height < MIN_DIMENSION_SIZE || MAX_DIMENSION_SIZE < m_height))
	{
		throw std::invalid_argument("Image sizes must have appropriate values");
	}
}
