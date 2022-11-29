#pragma once
#include "../AbstractLineStyle.h"

constexpr Thickness DEFUALT_THICKNESS = 1;

class SimpleLineStyle : public AbstractLineStyle
{
public:
	SimpleLineStyle(RGBAColor color, bool isEnabled = true, Thickness thickness = DEFUALT_THICKNESS);

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor) override;

	std::optional<unsigned int> GetThickness() const override;
	void SetThickness(const Thickness) override;

private:
	RGBAColor m_color;
	Thickness m_thickness;
};
