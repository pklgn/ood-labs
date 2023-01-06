#pragma once
#include "../Canvas/ICanvas.h"

class IDrawable
{
public:
	virtual ~IDrawable() = default;

	virtual void Draw(ICanvas&) = 0;
};