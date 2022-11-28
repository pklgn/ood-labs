#include "../../../pch.h"
#include "Ellipse.h"

Ellipse::Ellipse(const Point& leftTop,
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

void Ellipse::Draw(ICanvas& canvas)
{
	auto lineColor = GetLineStyle()->GetColor().value_or(0xFFFFFFFF);
	canvas.SetLineColor(lineColor);

	auto fillColor = GetFillStyle()->GetColor().value_or(0xFFFFFFFF);
	canvas.SetFillColor(fillColor);

	auto thickness = GetLineStyle()->GetThickness().value_or(1);
	canvas.SetLineThickness(thickness);

	canvas.DrawEllipse(m_leftTop, m_width, m_height);
}
