#include "../pch.h"
#include "Ellipse.h"

Ellipse::Ellipse(const Point& center, float horizontalRadius, float verticalRaduis, const Color& color)
	: Shape(color)
	, m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRaduis(verticalRaduis)
{
}

void Ellipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());

	Point leftTop = { m_center.x - m_horizontalRadius, m_center.y + m_verticalRaduis };
	canvas.DrawEllipse(leftTop, m_horizontalRadius * 2, m_verticalRaduis * 2);
}

Point Ellipse::GetCenter() const
{
	return m_center;
}

float Ellipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

float Ellipse::GetVerticalRaduis() const
{
	return m_verticalRaduis;
}
