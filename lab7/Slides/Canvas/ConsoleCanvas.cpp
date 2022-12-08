#include "../pch.h"
#include "ConsoleCanvas.h"

const unsigned int DEFAULT_CANVAS_LINE_THICKNESS = 1;

ConsoleCanvas::ConsoleCanvas(std::ostream& output)
	: m_output(output)
	, m_lineColor(0x000000FF)
	, m_fillColor(0xFFFFFFFF)
	, m_lineThickness(DEFAULT_CANVAS_LINE_THICKNESS)
{
}

void ConsoleCanvas::DrawLine(const Point& from, const Point& to)
{
	m_output << "DrawLine\n"
			 << from << '\n'
			 << to << '\n';
}

void ConsoleCanvas::DrawClosedPolyLine(std::vector<Point>& points)
{
	//FIXED: implement
	m_output << "DrawClosedPolyLine\n";
	for (auto& point : points)
	{
		m_output << '\t' << point << '\n';
	}
}

void ConsoleCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	m_output << "DrawEllipse\n"
			  << "\tleftTop: " << leftTop << "\n"
			  << "\twidth:\t" << width << "\n"
			  << "\theight:\t" << height << "\n";
}

void ConsoleCanvas::FillEllipse(const Point& leftTop, double width, double height)
{
	m_output << "FillEllipse\n"
			  << "\tleftTop: " << leftTop << "\n"
			  << "\twidth: " << width << "\n"
			  << "\theight: " << height << "\n"
			  << "\tcolor: " << std::hex << m_fillColor << "\n";
}

void ConsoleCanvas::FillPolygon(std::vector<Point>& points)
{
	m_output << "FillPolygon\n";
	for (auto& point: points)
	{
		m_output << '\t' << point << '\n';
	}
	m_output << "\tcolor: " << std::hex << m_fillColor << "\n";
}

void ConsoleCanvas::SetFillColor(uint32_t color)
{
	m_fillColor = color;
	m_output << "SetFillColor\n"
			 << '\t' << std::hex << color << std::dec << '\n';
}

void ConsoleCanvas::SetLineColor(uint32_t color)
{
	m_lineColor = color;
	m_output << "SetLineColor\n"
			 << '\t' << std::hex << color << std::dec << '\n';
}

void ConsoleCanvas::SetLineThickness(unsigned int thickness)
{
	m_lineThickness = thickness;
	m_output << "SetLineThickness\n"
			 << '\t' << thickness << '\n';
}
