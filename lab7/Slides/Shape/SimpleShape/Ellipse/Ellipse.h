#pragma once
#include "../SimpleShape.h"

class Ellipse : public SimpleShape
{
public:
	Ellipse(const Point& leftTop,
		double width,
		double height,
		const std::shared_ptr<ILineStyle> = std::make_shared<SimpleLineStyle>(),
		const std::shared_ptr<IFillStyle> = std::make_shared<SimpleFillStyle>());

	RectD GetFrame() override;
	void SetFrame(const RectD&) override;

	void Draw(ICanvas&) override;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};
