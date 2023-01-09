#include "../../../pch.h"
#include "FillStyle.h"

const RGBAColor DEFAULT_COLOR = 0x2F528FFF;

FillStyle::FillStyle()
	: m_color(DEFAULT_COLOR)
{
}

std::optional<RGBAColor> FillStyle::GetColor() const
{
	return m_color;
}
