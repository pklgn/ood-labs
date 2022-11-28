#include "../../../pch.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Point& leftTop,
	double width,
	double height,
	const std::shared_ptr<SimpleLineStyle> lineStyle,
	const std::shared_ptr<SimpleFillStyle> fillStyle
)
	: SimpleShape(RectD{leftTop.x, leftTop.y, width, height}, lineStyle, fillStyle)
	, m_width(width)
	, m_height(height)
{
}

void Rectangle::Draw(ICanvas& canvas)
{
	Point rightBottom = { m_leftTop.x + m_width, m_leftTop.y + m_height };
	Point rightTop = { rightBottom.x, m_leftTop.y };
	Point leftBottom = { m_leftTop.x, rightBottom.y };

	auto lineColor = GetLineStyle()->GetColor().value_or(0xFFFFFFFF);
	canvas.SetLineColor(lineColor);

	auto fillColor = GetFillStyle()->GetColor().value_or(0xFFFFFFFF);
	canvas.SetFillColor(fillColor);

	auto thickness = GetLineStyle()->GetThickness().value_or(1);
	canvas.SetLineThickness(thickness);

	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, rightBottom);
	canvas.DrawLine(rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);
}
