#include "../../pch.h"
#include "MenuView.h"
#include "../../common/Frame/Frame.h"

MenuView::MenuView(size_t width, size_t height, size_t offsetY)
	: m_width(width)
	, m_height(height)
	, m_offsetY(offsetY)
{
	m_buttons = {
		"Add Triangle",
		"Add Rectangle",
		"Add Ellipse",
		"Undo",
		"Redo",
	};
}


size_t MenuView::GetWidth() const
{
	return m_width;
}

size_t MenuView::GetHeight() const
{
	return m_height;
}

void ShowButton(ICanvas& canvas, const RectD& frame)
{
	canvas.SetLineColor(0xFFFFFFFF);
	auto thickness = 2;
	canvas.SetLineThickness(thickness);

	Point leftTop = { frame.left, frame.top };
	Point rightBottom = { frame.left + frame.width, frame.top + frame.height };
	Point rightTop = { rightBottom.x, leftTop.y };
	Point leftBottom = { leftTop.x, rightBottom.y };

	canvas.DrawLine({ leftTop.x - thickness, leftTop.y }, { rightTop.x + thickness, rightTop.y });
	canvas.DrawLine(rightTop, rightBottom);
	canvas.DrawLine({ rightBottom.x + thickness, rightBottom.y }, { leftBottom.x - thickness, leftBottom.y });
	canvas.DrawLine(leftBottom, leftTop);
}

void MenuView::Show(ICanvas& canvas)
{
	auto width = (double)m_width;
	auto height = (double)m_height;

	ShowButton(canvas, { 0, m_offsetY, width, height });
	ShowButton(canvas, { 0 + width * 1 / 5, m_offsetY, width * 1 / 5, height });
	ShowButton(canvas, { 0 + width * 2 / 5, m_offsetY, width * 1 / 5, height });
	ShowButton(canvas, { 0 + width * 3 / 5, m_offsetY, width * 1 / 5, height });
	ShowButton(canvas, { 0 + width * 4 / 5, m_offsetY, width * 1 / 5, height });
}
