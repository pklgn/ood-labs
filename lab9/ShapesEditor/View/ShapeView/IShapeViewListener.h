#pragma once
#include "../../common/Point/Point.h"

class IShapeViewListener
{
public:
	virtual ~IShapeViewListener() = default;

	virtual void OnMouseDown(const Point&) = 0;
	virtual void OnDrag(const Point&) = 0;
	virtual void OnMouseUp(const Point&) = 0;
};