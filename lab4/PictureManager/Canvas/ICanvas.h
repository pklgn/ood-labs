#pragma once

const size_t ELLIPSE_POINT_COUNT = 30;

enum class Color
{
	Green = 0x00d678,
	Red = 0xee4b2b,
	Blue = 0x0096ff,
	Yellow = 0xffea00,
	Pink = 0xe5acb6,
	Black = 0x000000,
};

struct Point
{
	float x;
	float y;

	friend std::istream& operator>>(std::istream& inputStream, Point& point)
	{
		inputStream >> point.x >> point.y;

		return inputStream;
	}
};

class ICanvas
{
public:
	virtual void SetColor(Color) = 0;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& leftTop, float width, float height, size_t pointCount = ELLIPSE_POINT_COUNT) = 0;

	virtual ~ICanvas() = default;
};