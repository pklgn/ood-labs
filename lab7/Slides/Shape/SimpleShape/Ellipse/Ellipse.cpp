#include "../../../pch.h"
#include "Ellipse.h"

Ellipse::Ellipse(const Point& leftTop,
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

RectD Ellipse::GetFrame()
{
	return RectD{ m_leftTop.x, m_leftTop.y, m_width, m_height };
}

void Ellipse::SetFrame(const RectD& frame)
{
	SimpleShape::SetFrame(frame);

	m_leftTop = Point{ frame.left, frame.top };
	m_width = frame.width;
	m_height = frame.height;
}

void Ellipse::Draw(ICanvas& canvas)
{
	auto fillStyle = GetFillStyle();
	if (fillStyle->IsEnabled())
	{
		auto fillColor = GetFillStyle()->GetColor().value_or(DEFAULT_FILL_COLOR);
		canvas.SetFillColor(fillColor);
		canvas.FillEllipse(m_leftTop, m_width, m_height);
	}

	auto lineStyle = GetLineStyle();
	if (lineStyle->IsEnabled())
	{
		auto lineColor = lineStyle->GetColor().value_or(DEFAULT_LINE_COLOR);
		canvas.SetLineColor(lineColor);

		auto thickness = GetLineStyle()->GetThickness().value_or(DEFAULT_LINE_THICKNESS);
		canvas.SetLineThickness(thickness);

		canvas.DrawEllipse(m_leftTop, m_width, m_height);
	}
}
