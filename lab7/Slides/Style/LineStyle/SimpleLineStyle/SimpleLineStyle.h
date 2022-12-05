#pragma once
#include "../AbstractLineStyle.h"

constexpr Thickness DEFUALT_THICKNESS = 1;

class SimpleLineStyle : public AbstractLineStyle
{
public:
	SimpleLineStyle(RGBAColor color, Thickness thickness = DEFUALT_THICKNESS, bool isEnabled = true);

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor) override;

	std::optional<Thickness> GetThickness() const override;
	void SetThickness(const Thickness) override;

private:
	RGBAColor m_color;
	Thickness m_thickness;
};
