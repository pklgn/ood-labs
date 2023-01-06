#pragma once
#include "../AbstractLineStyle.h"


class SimpleLineStyle : public AbstractLineStyle
{
public:
	SimpleLineStyle();
	SimpleLineStyle(RGBAColor color, Thickness thickness, bool isEnabled = true);

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor) override;

	std::optional<Thickness> GetThickness() const override;
	void SetThickness(const Thickness) override;

private:
	RGBAColor m_color;
	Thickness m_thickness;
};
