#pragma once

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