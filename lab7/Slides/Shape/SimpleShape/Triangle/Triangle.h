#pragma once
#include "../SimpleShape.h"

class Triangle : public SimpleShape
{
public:
	Triangle(const Point& vertexA,
		const Point& vertexB,
		const Point& vertexC,
		const std::shared_ptr<ILineStyle> = std::make_shared<SimpleLineStyle>(),
		const std::shared_ptr<IFillStyle> = std::make_shared<SimpleFillStyle>());

	RectD GetFrame() override;
	void SetFrame(const RectD&) override;

	void Draw(ICanvas&) override;

private:
	double GetFrameDimension(double Point::*);

	Point m_vertexA;
	Point m_vertexB;
	Point m_vertexC;
};
