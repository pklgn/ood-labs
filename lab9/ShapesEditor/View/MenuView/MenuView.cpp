#include "../../pch.h"
#include "MenuView.h"
#include "../../common/Frame/Frame.h"

const unsigned int DEFAULT_BUTTON_THICKNESS = 2;
const uint32_t DEFAULT_BUTTON_FILL_COLOR = 0xF3F3F3FF;
const uint32_t DEFAULT_BUTTON_LINE_COLOR = 0xB1B1B1FF;
const unsigned int DEFAULT_BUTTON_INDENT = 10; 

MenuView::MenuView(size_t width, size_t height, size_t offsetY)
	: m_width(width)
	, m_height(height)
	, m_offsetY(offsetY)
{
	m_buttons = {
		"Ins Triangle",
		"Ins Rectangle",
		"Ins Ellipse",
		"Del",
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

void ShowButton(ICanvas& canvas, const RectD& frame, const std::string& string)
{
	Point leftTop = { frame.left, frame.top };
	Point rightBottom = { frame.left + frame.width, frame.top + frame.height };
	Point rightTop = { rightBottom.x, leftTop.y };
	Point leftBottom = { leftTop.x, rightBottom.y };

	canvas.SetFillColor(DEFAULT_BUTTON_FILL_COLOR);
	canvas.FillPolygon({ leftTop, rightTop, rightBottom, leftBottom });

	canvas.SetFillColor(0xFFFFFFFF);
	auto thickness = DEFAULT_BUTTON_THICKNESS;
	canvas.SetLineThickness(thickness);

	canvas.SetFillColor(DEFAULT_BUTTON_LINE_COLOR);

	canvas.DrawLine({ leftTop.x - thickness, leftTop.y + DEFAULT_BUTTON_THICKNESS }, { rightTop.x + thickness, rightTop.y + DEFAULT_BUTTON_THICKNESS });
	canvas.DrawLine(rightTop, rightBottom);
	canvas.DrawLine({ rightBottom.x + thickness, rightBottom.y }, { leftBottom.x - thickness, leftBottom.y });
	canvas.DrawLine(leftBottom, leftTop);

	canvas.DrawText(string, {leftTop.x + DEFAULT_BUTTON_INDENT, leftTop.y + DEFAULT_BUTTON_INDENT});
}

void MenuView::Show(ICanvas& canvas)
{
	auto width = (double)m_width;
	auto height = (double)m_height;

	ShowButton(canvas, { 0 + DEFAULT_BUTTON_THICKNESS, m_offsetY, width, height }, m_buttons[0]);
	ShowButton(canvas, { 0 + width * 1 / 6, m_offsetY, width * 1 / 6, height }, m_buttons[1]);
	ShowButton(canvas, { 0 + width * 2 / 6, m_offsetY, width * 1 / 6, height }, m_buttons[2]);
	ShowButton(canvas, { 0 + width * 3 / 6, m_offsetY, width * 1 / 6, height }, m_buttons[3]);
	ShowButton(canvas, { 0 + width * 4 / 6, m_offsetY, width * 1 / 6, height }, m_buttons[4]);
	ShowButton(canvas, { 0 + width * 5 / 6, m_offsetY, width * 1 / 6 - DEFAULT_BUTTON_THICKNESS, height }, m_buttons[5]);
}
