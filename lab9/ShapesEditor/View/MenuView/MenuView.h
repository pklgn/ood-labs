#pragma once
#include <vector>
#include <functional>
#include "../IView.h"
#include "IMenuViewListener.h"

class MenuView : public IView
{
public:
	MenuView(size_t width, size_t height, size_t offsetY);

	size_t GetWidth() const;
	size_t GetHeight() const;

	void Show(ICanvas&) override;

private:
	std::vector<std::string> m_buttons;
	size_t m_width;
	size_t m_height;
	double m_offsetY;
};