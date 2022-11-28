#include "../../../pch.h"
#include "SimpleLineStyle.h"

SimpleLineStyle::SimpleLineStyle(RGBAColor color, bool isEnabled, Thickness thickness)
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

std::optional<uint8_t> SimpleLineStyle::GetThickness() const
{
	return m_thickness;
}

void SimpleLineStyle::SetThickness(const Thickness thickness)
{
	m_thickness = thickness;
}
