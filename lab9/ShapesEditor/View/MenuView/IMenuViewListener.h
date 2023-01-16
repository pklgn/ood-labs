#pragma once
#include "../../common/Point/Point.h"

class IMenuViewListener
{
public:
	virtual ~IMenuViewListener() = default;

	virtual void OnMouseDown(const Point&) = 0;
};