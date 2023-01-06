#include "../../../pch.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Point& leftTop,
	double width,
	double height,
	const std::shared_ptr<ILineStyle> lineStyle,
	const std::shared_ptr<IFillStyle> fillStyle
)
	: SimpleShape(lineStyle, fillStyle)
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

RectD Rectangle::GetFrame()
{
	return RectD{ m_leftTop.x, m_leftTop.y, m_width, m_height };
}

void Rectangle::SetFrame(const RectD& frame)
{
	SimpleShape::SetFrame(frame);

	m_leftTop = Point{ frame.left, frame.top };
	m_width = frame.width;
	m_height = frame.height;
}

void Rectangle::Draw(ICanvas& canvas)
{
	Point rightBottom = { m_leftTop.x + m_width, m_leftTop.y + m_height };
	Point rightTop = { rightBottom.x, m_leftTop.y };
	Point leftBottom = { m_leftTop.x, rightBottom.y };

	auto fillStyle = GetFillStyle();
	if (fillStyle->IsEnabled())
	{
		auto fillColor = fillStyle->GetColor().value_or(DEFAULT_FILL_COLOR);
		canvas.SetFillColor(fillColor);
		
		std::vector<Point> points{ m_leftTop, rightTop, rightBottom, leftBottom };
		canvas.FillPolygon(points);
	}

	auto lineStyle = GetLineStyle();
	if (lineStyle->IsEnabled())
	{
		auto lineColor = lineStyle->GetColor().value_or(DEFAULT_LINE_COLOR);
		canvas.SetLineColor(lineColor);

		auto thickness = GetLineStyle()->GetThickness().value_or(DEFAULT_LINE_THICKNESS);
		canvas.SetLineThickness(thickness);

		canvas.DrawLine({ m_leftTop.x - thickness, m_leftTop.y }, {rightTop.x + thickness, rightTop.y});
		canvas.DrawLine(rightTop, rightBottom);
		canvas.DrawLine({ rightBottom.x + thickness, rightBottom.y }, { leftBottom.x - thickness, leftBottom.y });
		canvas.DrawLine(leftBottom, m_leftTop);
	}
}
