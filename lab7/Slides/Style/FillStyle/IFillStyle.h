#pragma once
#include <optional>
#include "../../Color/Color.h"

class IFillStyle
{
public:
	virtual ~IFillStyle() = default;

	virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(const RGBAColor) = 0;

	virtual bool IsEnabled() const = 0;
	virtual void Enable() = 0;
	virtual void Disable() = 0;
};
