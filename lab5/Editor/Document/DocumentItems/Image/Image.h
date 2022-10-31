#pragma once

#include "IImage.h"

class Image : public IImage
{
public:
	Image(size_t width, size_t height, Path);

	Path GetPath() const override;

	size_t GetWidth() const override;

	size_t GetHeight() const override;

	void Resize(int width, int height) override;

private:
	size_t m_width;
	size_t m_height;
	Path m_path;
};