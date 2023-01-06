#pragma once
#include <functional>
#include "../IFillStyle.h"

class IFillStyleEnumerator
{
public:
	virtual ~IFillStyleEnumerator() = default;

	virtual void EnumerateAll(std::function<void(std::shared_ptr<IFillStyle>)>) = 0;
};