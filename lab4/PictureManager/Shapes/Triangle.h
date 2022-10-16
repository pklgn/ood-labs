#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(const Point&, const Point&, const Point&, const Color&);

	void Draw(ICanvas&) const override;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
