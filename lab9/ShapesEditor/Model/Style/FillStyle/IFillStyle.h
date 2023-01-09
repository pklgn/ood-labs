#pragma once
#include <optional>
#include "../../../common/Color/Color.h"

class IFillStyle
{
public:
	virtual ~IFillStyle() = default;

	virtual std::optional<RGBAColor> GetColor() const = 0;
};
