#pragma once
#include <istream>
#include <vector>

struct Point
{
	double x;
	double y;

	friend std::istream& operator>>(std::istream& inputStream, Point& point)
	{
		inputStream >> point.x >> point.y;

		return inputStream;
	}
};

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& leftTop, float width, float height) = 0;
	virtual void FillEllipse() = 0;
	virtual void FillPolygon(std::vector<Point>&) = 0;
	virtual void SetFillColor(uint32_t) = 0;
	virtual void SetLineColor(uint32_t) = 0;
	virtual void SetLineThickness(uint8_t) = 0;
};