#pragma once
#include <istream>
#include <vector>
#include "../../common/Point/Point.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawClosedPolyLine(const std::vector<Point>&) = 0;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) = 0;
	virtual void FillEllipse(const Point& leftTop, double width, double height) = 0;
	virtual void FillPolygon(const std::vector<Point>&) = 0;
	virtual void SetFillColor(uint32_t) = 0;
	virtual void SetLineColor(uint32_t) = 0;
	virtual void SetLineThickness(unsigned int) = 0;
};