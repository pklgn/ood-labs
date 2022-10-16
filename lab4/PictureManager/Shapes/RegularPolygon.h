#pragma once
#include "Shape.h"

class RegularPolygon : public Shape
{
public:
	RegularPolygon(const Point& center, size_t vertexCount, float radius, const Color& color);

	void Draw(ICanvas&) const;
	size_t GetVertexCount() const;
	Point GetCenter() const;
	float GetRaduis() const;

private:
	size_t m_vertexCount;
	Point m_center;
	float m_radius;
};
