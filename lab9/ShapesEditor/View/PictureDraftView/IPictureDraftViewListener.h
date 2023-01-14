#pragma once
#include "../../common/Point/Point.h"

class IPictureDraftViewListener
{
public:
	virtual ~IPictureDraftViewListener() = default;

	virtual void OnMouseDown(const Point&) = 0;
	virtual void OnMouseUp(const Point&) = 0;
};