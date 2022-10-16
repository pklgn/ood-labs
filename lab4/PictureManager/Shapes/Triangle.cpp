#include "../pch.h"
#include "Triangle.h"

Triangle::Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, const Color& color)
	: Shape(color)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

void Triangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());

	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex1, m_vertex3);
}

Point Triangle::GetVertex1() const
{
	return m_vertex1;
}

Point Triangle::GetVertex2() const
{
	return m_vertex2;
}

Point Triangle::GetVertex3() const
{
	return m_vertex3;
}