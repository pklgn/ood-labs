#pragma once
#include <optional>
#include "../../Color/Color.h"

typedef uint8_t Thickness;

class ILineStyle
{
public:
	virtual ~ILineStyle() = default;

	virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(const RGBAColor) = 0;

	virtual bool IsEnabled() const = 0;
	virtual void Enable() = 0;
	virtual void Disable() = 0;

	virtual std::optional<uint8_t> GetThickness() const = 0;
	virtual void SetThickness(const Thickness) = 0;
};