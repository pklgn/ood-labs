#pragma once
#include "../SimpleShape.h"

class Rectangle : public SimpleShape
{
public:
	Rectangle(const Point& leftTop,
		double width,
		double height,
		const std::shared_ptr<SimpleLineStyle> lineStyle,
		const std::shared_ptr<SimpleFillStyle> fillStyle
	);

	RectD GetFrame() override;
	void SetFrame(const RectD&) override;

	void Draw(ICanvas&) override;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};
