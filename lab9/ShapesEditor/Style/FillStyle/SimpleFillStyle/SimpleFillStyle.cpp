#include "../../../pch.h"
#include "SimpleFillStyle.h"

const RGBAColor DEFAULT_COLOR = 0x2F528FFF;

SimpleFillStyle::SimpleFillStyle()
	: m_color(DEFAULT_COLOR)
{
}

std::optional<RGBAColor> SimpleFillStyle::GetColor() const
{
	return m_color;
}
