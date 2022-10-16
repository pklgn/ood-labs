#include "../pch.h"
#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(const Point& center, size_t vertexCount, float radius, const Color& color)
	: Shape(color)
	, m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
}

void RegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	
	//Point leftTop = { m_center.x + m_radius, m_center.y - m_radius };

	canvas.DrawEllipse(m_center, m_radius, m_radius, m_vertexCount);
}

size_t RegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

Point RegularPolygon::GetCenter() const
{
	return m_center;
}

float RegularPolygon::GetRaduis() const
{
	return m_radius;
}
