#include "../../../pch.h"
#include "CompositeLineStyle.h"

CompositeLineStyle::CompositeLineStyle(std::unique_ptr<ILineStyleEnumerator> emumeratorPtr, bool isEnabled)
	: AbstractLineStyle(isEnabled)
	, m_enumeratorPtr(std::move(emumeratorPtr))
{
	m_color = GetColor();
	m_thickness = GetThickness();
}

//TODO: probably we should extract enumerator to style directory and define methods
//to 
// [](std::shared_ptr<ILineStyle> stylePtr)->T {return stylePtr->GetColor();}
std::optional<RGBAColor> CompositeLineStyle::GetColor() const
{
	std::optional<RGBAColor> prevColor = std::nullopt;
	std::optional<RGBAColor> currColor = std::nullopt;
	std::optional<RGBAColor> resultColor = std::nullopt;

	m_enumeratorPtr->EnumerateAll([&](std::shared_ptr<ILineStyle> stylePtr) {
		currColor = stylePtr->GetColor();
		if (prevColor == std::nullopt)
		{
			prevColor = currColor;
			resultColor = currColor;
		}
		
		if (resultColor != std::nullopt &&
			prevColor != currColor)
		{
			resultColor = std::nullopt;
		}
	});

	return resultColor;
}

void CompositeLineStyle::SetColor(const RGBAColor color)
{
	m_enumeratorPtr->EnumerateAll([color](std::shared_ptr<ILineStyle> stylePtr) {
		stylePtr->SetColor(color);
	});
}

std::optional<Thickness> CompositeLineStyle::GetThickness() const
{
	std::optional<Thickness> prevThickness = std::nullopt;
	std::optional<Thickness> currThickness = std::nullopt;
	std::optional<Thickness> resultThickness = std::nullopt;

	m_enumeratorPtr->EnumerateAll([&](std::shared_ptr<ILineStyle> stylePtr) {
		currThickness = stylePtr->GetThickness();
		if (prevThickness == std::nullopt)
		{
			prevThickness = currThickness;
			resultThickness = currThickness;
		}

		if (resultThickness != std::nullopt && prevThickness != currThickness)
		{
			resultThickness = std::nullopt;
		}
	});

	return resultThickness;
}

void CompositeLineStyle::SetThickness(const Thickness thickness)
{
	m_enumeratorPtr->EnumerateAll([thickness](std::shared_ptr<ILineStyle> stylePtr) {
		stylePtr->SetThickness(thickness);
	});
}
