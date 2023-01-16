#include "../../../pch.h"
#include "LineStyle.h"

const RGBAColor DEFAULT_COLOR = 0xFFFFFFFF;
const Thickness DEFAULT_THICKENSS = 1;

LineStyle::LineStyle()
	: m_color(DEFAULT_COLOR)
	, m_thickness(DEFAULT_THICKENSS)
{
}

std::optional<RGBAColor> LineStyle::GetColor() const
{
	return m_color;
}

std::optional<Thickness> LineStyle::GetThickness() const
{
	return m_thickness;
}
