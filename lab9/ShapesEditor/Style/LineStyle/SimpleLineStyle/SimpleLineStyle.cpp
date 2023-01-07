#include "../../../pch.h"
#include "SimpleLineStyle.h"

const RGBAColor DEFAULT_COLOR = 0xFFFFFFFF;
const Thickness DEFAULT_THICKENSS = 1;

SimpleLineStyle::SimpleLineStyle()
	: m_color(DEFAULT_COLOR)
	, m_thickness(DEFAULT_THICKENSS)
{
}

std::optional<RGBAColor> SimpleLineStyle::GetColor() const
{
	return m_color;
}

std::optional<Thickness> SimpleLineStyle::GetThickness() const
{
	return m_thickness;
}
