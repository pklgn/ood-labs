#include "../../../pch.h"
#include "CompositeFillStyle.h"

CompositeFillStyle::CompositeFillStyle(std::unique_ptr<IFillStyleEnumerator> emumeratorPtr, bool isEnabled)
	: AbstractFillStyle(isEnabled)
	, m_enumeratorPtr(std::move(emumeratorPtr))
{
	m_color = GetColor();
}

std::optional<RGBAColor> CompositeFillStyle::GetColor() const
{
	std::optional<RGBAColor> prevColor = std::nullopt;
	std::optional<RGBAColor> currColor = std::nullopt;
	std::optional<RGBAColor> resultColor = std::nullopt;

	m_enumeratorPtr->EnumerateAll([&](std::shared_ptr<IFillStyle> stylePtr) {
		currColor = stylePtr->GetColor();
		if (prevColor == std::nullopt)
		{
			prevColor = currColor;
			resultColor = currColor;
		}

		if (resultColor != std::nullopt && prevColor != currColor)
		{
			resultColor = std::nullopt;
		}
	});

	return resultColor;
}

void CompositeFillStyle::SetColor(const RGBAColor color)
{
	m_enumeratorPtr->EnumerateAll([color](std::shared_ptr<IFillStyle> stylePtr) {
		stylePtr->SetColor(color);
	});
}

void CompositeFillStyle::Enable()
{
	m_enumeratorPtr->EnumerateAll([](std::shared_ptr<IFillStyle> stylePtr) {
		stylePtr->Enable();
	});

	m_isEnabled = true;
}

void CompositeFillStyle::Disable()
{
	m_enumeratorPtr->EnumerateAll([](std::shared_ptr<IFillStyle> stylePtr) {
		stylePtr->Disable();
	});

	m_isEnabled = false;
}
