#pragma once
#include <memory>
#include "../AbstractLineStyle.h"
#include "../Enumerator/ILineStyleEnumerator.h"

class CompositeLineStyle : public AbstractLineStyle
{
public:
	CompositeLineStyle(std::unique_ptr<ILineStyleEnumerator>, bool isEnabled = true);

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor) override;

	std::optional<unsigned int> GetThickness() const override;
	void SetThickness(const Thickness) override;

private:
	std::unique_ptr<ILineStyleEnumerator> m_enumeratorPtr;
	std::optional<RGBAColor> m_color;
	std::optional<Thickness> m_thickness;
};
