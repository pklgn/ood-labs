#pragma once
#include "IFillStyle.h"

class FillStyle : public IFillStyle
{
public:
	FillStyle();

	std::optional<RGBAColor> GetColor() const override;

private:
	RGBAColor m_color;
};
