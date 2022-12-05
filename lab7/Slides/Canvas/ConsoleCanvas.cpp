#include "../pch.h"
#include "ConsoleCanvas.h"

void ConsoleCanvas::DrawLine(const Point& from, const Point& to)
{
	std::cout << "DrawLine\n\tfrom:\t"
			  << from
			  << "\n\tto:\t"
			  << to
			  << std::endl;
}

void ConsoleCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	std::cout << "DrawEllipse with\n"
			  << "\tleftTop: " << leftTop << "\n"
			  << "\twidth:\t" << width << "\n"
			  << "\theight:\t" << height << "\n";
}

void ConsoleCanvas::FillEllipse(const Point& leftTop, double width, double height)
{
	std::cout << "FillEllipse with\n"
			  << "\tleftTop: " << leftTop << "\n"
			  << "\twidth: " << width << "\n"
			  << "\theight: " << height << "\n"
			  << "\tcolor: " << std::hex << m_fillColor << "\n";
}

void ConsoleCanvas::FillPolygon(std::vector<Point>& points)
{
	std::cout << "FillPolygon with\n";
	for (auto& point: points)
	{
		std::cout << "\tpoint: " << point << "\n";
	}
	std::cout << "\tcolor: " << std::hex << m_fillColor << "\n";
}

void ConsoleCanvas::SetFillColor(uint32_t color)
{
	m_fillColor = color;
	std::cout << "SetFillColor: " << std::hex << color << std::dec << "\n";
}

void ConsoleCanvas::SetLineColor(uint32_t color)
{
	m_lineColor = color;
	std::cout << "SetLineColor: " << std::hex << color << std::dec << "\n";
}

void ConsoleCanvas::SetLineThickness(unsigned int thickness)
{
	m_lineThickness = thickness;
	std::cout << "SetLineThickness: " << thickness << "\n";
}
