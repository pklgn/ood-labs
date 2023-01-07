#pragma once
#include "../ILineStyle.h"


class SimpleLineStyle : public ILineStyle
{
public:
	SimpleLineStyle();

	std::optional<RGBAColor> GetColor() const override;
	std::optional<Thickness> GetThickness() const override;

private:
	RGBAColor m_color;
	Thickness m_thickness;
};
