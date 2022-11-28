#include "../../../pch.h"
#include "Triangle.h"

Triangle::Triangle(const Point& vertexA, const Point& vertexB, const Point& vertexC, const std::shared_ptr<SimpleLineStyle> lineStyle, const std::shared_ptr<SimpleFillStyle> fillStyle)
	: SimpleShape(CalculateFrame(vertexA, vertexB, vertexC), lineStyle, fillStyle)
	, m_vertexA(vertexA)
	, m_vertexB(vertexB)
	, m_vertexC(vertexC)
{
}

void Triangle::Draw(ICanvas& canvas)
{
	auto lineColor = GetLineStyle()->GetColor().value_or(0xFFFFFFFF);
	canvas.SetLineColor(lineColor);

	auto fillColor = GetFillStyle()->GetColor().value_or(0xFFFFFFFF);
	canvas.SetFillColor(fillColor);

	auto thickness = GetLineStyle()->GetThickness().value_or(1);
	canvas.SetLineThickness(thickness);

	canvas.DrawLine(m_vertexA, m_vertexB);
	canvas.DrawLine(m_vertexB, m_vertexC);
	canvas.DrawLine(m_vertexC, m_vertexA);
}

double GetFrameDimension(double Point::*dim, const Point& vertexA, const Point& vertexB, const Point& vertexC)
{
	auto dimAB = std::abs(vertexA.*dim - vertexB.*dim);
	auto dimBC = std::abs(vertexB.*dim - vertexC.*dim);
	auto dimAC = std::abs(vertexA.*dim - vertexC.*dim);

	return std::max(dimAB, std::max(dimBC, dimAC));
}

RectD Triangle::CalculateFrame(const Point& vertexA, const Point& vertexB, const Point& vertexC)
{
	double width;
	double height;

	width = GetFrameDimension(&Point::x, vertexA, vertexB, vertexC);
	height = GetFrameDimension(&Point::y, vertexA, vertexB, vertexC);

	auto left = std::min(vertexA.x, std::min(vertexB.x, vertexC.x));
	auto top = std::min(vertexA.y, std::min(vertexB.y, vertexC.y));

	return RectD{ left, top, width, height };
}
