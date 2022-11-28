#pragma once
#include "../SimpleShape.h"

class Triangle : public SimpleShape
{
public:
	Triangle(const Point& vertexA, const Point& vertexB, const Point& vertexC, const std::shared_ptr<SimpleLineStyle>, const std::shared_ptr<SimpleFillStyle>);

	void Draw(ICanvas&) override;

private:
	RectD CalculateFrame(const Point&, const Point&, const Point&);

	Point m_vertexA;
	Point m_vertexB;
	Point m_vertexC;
};
