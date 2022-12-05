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

	friend std::ostream& operator<<(std::ostream& outputStream, const Point& point)
	{
		outputStream << point.x << " " << point.y;

		return outputStream;
	}
};

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) = 0;
	virtual void FillEllipse(const Point& leftTop, double width, double height) = 0;
	virtual void FillPolygon(std::vector<Point>&) = 0;
	virtual void SetFillColor(uint32_t) = 0;
	virtual void SetLineColor(uint32_t) = 0;
	virtual void SetLineThickness(unsigned int) = 0;
};