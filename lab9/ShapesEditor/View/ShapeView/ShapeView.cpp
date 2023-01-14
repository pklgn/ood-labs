#include "../../pch.h"
#include "ShapeView.h"

const unsigned int DEFAULT_LINE_THICKNESS = 1;

ShapeView::ShapeView(const RectD& frame, ShapeType type, uint32_t lineColor, uint32_t fillColor)
	: m_frame(frame)
	, m_lineColor(lineColor)
	, m_fillColor(fillColor)
	, m_type(type)
{
}

void ShapeView::SetFrame(const RectD& frame)
{
	m_frame = frame;
}

RectD ShapeView::GetFrame() const
{
	return m_frame;
}

uint32_t ShapeView::GetLineColor() const
{
	return m_lineColor;
}

uint32_t ShapeView::GetFillColor() const
{
	return m_fillColor;
}

ShapeType ShapeView::GetShapeType() const
{
	return m_type;
}

void ShapeView::SetListener(std::shared_ptr<IShapeViewListener> listener)
{
	m_listener = listener;
}

void ShapeView::Show(ICanvas& canvas)
{
	switch (m_type)
	{
	case ShapeType::Rectangle:
		ShowRectangle(canvas);
		break;
	case ShapeType::Triangle:
		ShowTriangle(canvas);
		break;
	case ShapeType::Ellipse:
		ShowEllipse(canvas);
		break;
	default:
		break;
	}
}

void ShapeView::ShowRectangle(ICanvas& canvas)
{
	Point leftTop = { m_frame.left, m_frame.top };
	Point rightBottom = { m_frame.left + m_frame.width, m_frame.top + m_frame.height };
	Point rightTop = { rightBottom.x, m_frame.top };
	Point leftBottom = { m_frame.left, rightBottom.y };

	canvas.SetFillColor(m_fillColor);

	std::vector<Point> points{ leftTop, rightTop, rightBottom, leftBottom };
	canvas.FillPolygon(points);

	canvas.SetLineColor(m_lineColor);

	auto thickness = DEFAULT_LINE_THICKNESS;
	canvas.SetLineThickness(thickness);

	canvas.DrawLine({ leftTop.x - thickness, leftTop.y }, { rightTop.x + thickness, rightTop.y });
	canvas.DrawLine(rightTop, rightBottom);
	canvas.DrawLine({ rightBottom.x + thickness, rightBottom.y }, { leftBottom.x - thickness, leftBottom.y });
	canvas.DrawLine(leftBottom, leftTop);
}

void ShapeView::ShowTriangle(ICanvas& canvas)
{
	Point vertexA = { m_frame.left, m_frame.top + m_frame.height };
	Point vertexB = { m_frame.left + m_frame.width / 2, m_frame.top };
	Point vertexC = { m_frame.left + m_frame.width, m_frame.top + m_frame.height };

	auto points = std::vector<Point>{ vertexA, vertexB, vertexC };

	canvas.SetFillColor(m_fillColor);

	canvas.FillPolygon(points);

	canvas.SetLineColor(m_lineColor);

	canvas.SetLineThickness(DEFAULT_LINE_THICKNESS);

	canvas.DrawClosedPolyLine(points);
}

void ShapeView::ShowEllipse(ICanvas& canvas)
{
	canvas.SetFillColor(m_fillColor);
	Point leftTop = { m_frame.left, m_frame.top };
	canvas.FillEllipse(leftTop, m_frame.width, m_frame.height);

	canvas.SetLineColor(m_lineColor);

	canvas.SetLineThickness(DEFAULT_LINE_THICKNESS);

	canvas.DrawEllipse(leftTop, m_frame.width, m_frame.height);
}
