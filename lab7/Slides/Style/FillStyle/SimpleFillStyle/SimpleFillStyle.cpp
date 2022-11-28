#include "../../../pch.h"
#include "SimpleFillStyle.h"

SimpleFillStyle::SimpleFillStyle(RGBAColor color, bool isEnabled)
	: AbstractFillStyle(isEnabled)
	, m_color(color)
{
}

std::optional<RGBAColor> SimpleFillStyle::GetColor() const
{
	return m_color;
}

void SimpleFillStyle::SetColor(const RGBAColor color)
{
	m_color = color;
}