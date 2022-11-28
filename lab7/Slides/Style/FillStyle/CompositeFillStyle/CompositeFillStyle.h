#pragma once
#include <memory>
#include "../AbstractFillStyle.h"
#include "../Enumerator/IFillStyleEnumerator.h"

class CompositeFillStyle : public AbstractFillStyle
{
public:
	CompositeFillStyle(std::unique_ptr<IFillStyleEnumerator>, bool isEnabled = true);

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor) override;

private:
	std::unique_ptr<IFillStyleEnumerator> m_enumeratorPtr;
	std::optional<RGBAColor> m_color;
};