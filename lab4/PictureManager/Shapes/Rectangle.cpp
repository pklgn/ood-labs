#include "../pch.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Point& leftTop, const Point& rightBottom, const Color& color)
	: Shape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}

void Rectangle::Draw(ICanvas& canvas) const
{
	Point rightTop = { m_rightBottom.x, m_leftTop.y };
	Point leftBottom = { m_leftTop.x, m_rightBottom.y };

	canvas.SetColor(GetColor());

	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, m_rightBottom);
	canvas.DrawLine(m_rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);

	return;
}

Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return m_rightBottom;
}
