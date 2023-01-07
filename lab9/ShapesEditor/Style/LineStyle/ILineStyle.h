#pragma once
#include <optional>
#include "../../Color/Color.h"

typedef unsigned int Thickness;

class ILineStyle
{
public:
	virtual ~ILineStyle() = default;

	virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual std::optional<Thickness> GetThickness() const = 0;
};
