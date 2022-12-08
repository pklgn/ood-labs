#include "../../../pch.h"
#include "SimpleLineStyle.h"

const RGBAColor DEFAULT_COLOR = 0xFFFFFFFF;
const Thickness DEFAULT_THICKENSS = 1;

SimpleLineStyle::SimpleLineStyle(bool isEnabled)
	: AbstractLineStyle(isEnabled)
	, m_color(DEFAULT_COLOR)
	, m_thickness(DEFAULT_THICKENSS)
{
}

SimpleLineStyle::SimpleLineStyle(RGBAColor color, Thickness thickness, bool isEnabled)
	: AbstractLineStyle(isEnabled)
	, m_color(color)
	, m_thickness(thickness)
{
}

std::optional<RGBAColor> SimpleLineStyle::GetColor() const
{
	return m_color;
}

void SimpleLineStyle::SetColor(const RGBAColor color)
{
	m_color = color;
}

std::optional<unsigned int> SimpleLineStyle::GetThickness() const
{
	return m_thickness;
}

void SimpleLineStyle::SetThickness(const Thickness thickness)
{
	m_thickness = thickness;
}
