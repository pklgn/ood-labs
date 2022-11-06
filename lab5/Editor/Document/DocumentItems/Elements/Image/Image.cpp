#include "../../../../pch.h"
#include "Image.h"

constexpr size_t MIN_DIMENSION_SIZE = 1;
constexpr size_t MAX_DIMENSION_SIZE = 10000;

namespace fs = std::filesystem;

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

bool IsValidDimensions(size_t width, size_t height)
{
	return MIN_DIMENSION_SIZE <= width && width <= MAX_DIMENSION_SIZE && MIN_DIMENSION_SIZE <= height && height <= MAX_DIMENSION_SIZE;
}

void Image::Resize(size_t width, size_t height)
{
	if (!IsValidDimensions(width, height))
	{
		throw std::invalid_argument("Image sizes must have appropriate values");
	}

	m_width = width;
	m_height = height;
}

void Image::ValidateImage()
{
	if (!IsValidDimensions(m_width, m_height))
	{
		throw std::invalid_argument("Image sizes must have appropriate values");
	}

	if (!fs::exists(m_path))
	{
		throw std::invalid_argument("Image path can't be found");
	}
}
