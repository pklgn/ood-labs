#include "../../../pch.h"
#include "SimpleFillStyle.h"

const RGBAColor DEFAULT_COLOR = 0x2F528FFF;

SimpleFillStyle::SimpleFillStyle()
	: AbstractFillStyle(true)
	, m_color(DEFAULT_COLOR)
{
}

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