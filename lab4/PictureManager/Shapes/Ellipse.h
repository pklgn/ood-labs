#pragma once
#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(const Point& center, float horizontalRadius, float verticalRaduis, const Color& color);

	void Draw(ICanvas&) const override;
	Point GetCenter() const;
	float GetHorizontalRadius() const;
	float GetVerticalRaduis() const;

private:
	Point m_center;
	float m_horizontalRadius;
	float m_verticalRaduis;
};
