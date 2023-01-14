#pragma once
#include "Canvas/ICanvas.h"

class IView
{
public:
	virtual ~IView() = default;

	virtual void Show(ICanvas&) = 0;
};