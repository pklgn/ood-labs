#pragma once
#include "ILineStyle.h"


class LineStyle : public ILineStyle
{
public:
	LineStyle();

	std::optional<RGBAColor> GetColor() const override;
	std::optional<Thickness> GetThickness() const override;

private:
	RGBAColor m_color;
	Thickness m_thickness;
};
