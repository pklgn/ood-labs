#pragma once
#include <optional>
#include "../../Color/Color.h"

class IFillStyle
{
public:
	virtual ~IFillStyle() = default;

	virtual std::optional<RGBAColor> GetColor() const = 0;
};
