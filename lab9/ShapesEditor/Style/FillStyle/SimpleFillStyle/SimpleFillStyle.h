#pragma once
#include "../IFillStyle.h"

class SimpleFillStyle : public IFillStyle
{
public:
	SimpleFillStyle();

	std::optional<RGBAColor> GetColor() const override;

private:
	RGBAColor m_color;
};
