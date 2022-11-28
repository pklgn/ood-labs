#pragma once
#include "../SimpleShape.h"

class Ellipse : public SimpleShape
{
public:
	Ellipse(const Point& leftTop,
		double width,
		double height,
		const std::shared_ptr<SimpleLineStyle>,
		const std::shared_ptr<SimpleFillStyle>
	);

	void Draw(ICanvas&) override;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};
