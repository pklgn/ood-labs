#pragma once
#include "../IShape.h"
#include "../../Style/LineStyle/SimpleLineStyle/SimpleLineStyle.h"
#include "../../Style/FillStyle/SimpleFillStyle/SimpleFillStyle.h"

const RGBAColor DEFAULT_LINE_COLOR = 0xFFFFFFFF;
const RGBAColor DEFAULT_FILL_COLOR = 0xFFFFFFFF;
const Thickness DEFAULT_LINE_THICKNESS = 1;

class SimpleShape : public IShape
{
public:
	SimpleShape(const std::shared_ptr<ILineStyle>, const std::shared_ptr<IFillStyle>);

	std::shared_ptr<ILineStyle> GetLineStyle() override;
	std::shared_ptr<const ILineStyle> GetLineStyle() const override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	std::shared_ptr<const IFillStyle> GetFillStyle() const override;

	std::shared_ptr<const IShape> GetGroupShape() const override;

	void SetFrame(const RectD&) override;

private:
	std::shared_ptr<ILineStyle> m_lineStyle;
	std::shared_ptr<IFillStyle> m_fillStyle;
};
