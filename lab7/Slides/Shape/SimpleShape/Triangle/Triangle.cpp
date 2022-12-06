#include "../../../pch.h"
#include "Triangle.h"

void TransformVertexPoint(Point& point, const RectD& oldFrame, const RectD& newFrame);

Triangle::Triangle(const Point& vertexA, const Point& vertexB, const Point& vertexC, const std::shared_ptr<SimpleLineStyle> lineStyle, const std::shared_ptr<SimpleFillStyle> fillStyle)
	: SimpleShape(lineStyle, fillStyle)
	, m_vertexA(vertexA)
	, m_vertexB(vertexB)
	, m_vertexC(vertexC)
{
}

RectD Triangle::GetFrame()
{
	double width;
	double height;

	width = GetFrameDimension(&Point::x);
	height = GetFrameDimension(&Point::y);

	auto left = std::min(m_vertexA.x, std::min(m_vertexB.x, m_vertexC.x));
	auto top = std::min(m_vertexA.y, std::min(m_vertexB.y, m_vertexC.y));

	return RectD{ left, top, width, height };
}

void Triangle::SetFrame(const RectD& frame)
{
	auto currFrame = GetFrame();
	
	TransformVertexPoint(m_vertexA, currFrame, frame);
	TransformVertexPoint(m_vertexB, currFrame, frame);
	TransformVertexPoint(m_vertexC, currFrame, frame);
}

void Triangle::Draw(ICanvas& canvas)
{
	auto points = std::vector<Point>{ m_vertexA, m_vertexB, m_vertexC };

	auto fillStyle = GetFillStyle();
	if (fillStyle->IsEnabled())
	{
		auto fillColor = fillStyle->GetColor().value_or(DEFAULT_FILL_COLOR);
		canvas.SetFillColor(fillColor);

		canvas.FillPolygon(points);
	}

	auto lineStyle = GetLineStyle();
	if (lineStyle->IsEnabled())
	{
		auto lineColor = lineStyle->GetColor().value_or(DEFAULT_LINE_COLOR);
		canvas.SetLineColor(lineColor);

		auto thickness = lineStyle->GetThickness().value_or(DEFAULT_LINE_THICKNESS);
		canvas.SetLineThickness(thickness);

		canvas.DrawClosedPolyLine(points);
	}
}

double Triangle::GetFrameDimension(double Point::*dim)
{
	auto dimAB = std::abs(m_vertexA.*dim - m_vertexB.*dim);
	auto dimBC = std::abs(m_vertexB.*dim - m_vertexC.*dim);
	auto dimAC = std::abs(m_vertexA.*dim - m_vertexC.*dim);

	return std::max(dimAB, std::max(dimBC, dimAC));
}

void TransformVertexPoint(Point& point, const RectD& oldFrame, const RectD& newFrame)
{
	auto coefX = newFrame.width / oldFrame.width;
	auto coefY = newFrame.height / oldFrame.height;

	auto distanceX = point.x - oldFrame.left;
	auto distanceY = point.y - oldFrame.top;

	point.x = newFrame.left + distanceX * coefX;
	point.y = newFrame.top + distanceY * coefY;
}
