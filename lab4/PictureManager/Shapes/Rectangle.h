#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point& leftTop, const Point& rightBottom, const Color&);

	void Draw(ICanvas&) const override;
	Point GetLeftTop() const;
	Point GetRightBottom() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
};