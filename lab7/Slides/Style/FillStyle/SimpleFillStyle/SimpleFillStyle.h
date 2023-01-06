#pragma once
#include "../AbstractFillStyle.h"

class SimpleFillStyle : public AbstractFillStyle
{
public:
	SimpleFillStyle();
	SimpleFillStyle(RGBAColor color, bool isEnabled = true);

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor) override;

private:
	RGBAColor m_color;
};
