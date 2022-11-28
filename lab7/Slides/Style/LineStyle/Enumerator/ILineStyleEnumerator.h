#pragma once
#include <functional>
#include "../ILineStyle.h"

class ILineStyleEnumerator
{
public:
	virtual ~ILineStyleEnumerator() = default;

	virtual void EnumerateAll(std::function<void(std::shared_ptr<ILineStyle>)>) = 0;
};