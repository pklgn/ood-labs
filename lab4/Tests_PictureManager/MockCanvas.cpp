#include "MockCanvas.h"

MockCanvas::MockCanvas(std::ostream& output)
	: m_output(output)
{
}

void MockCanvas::SetColor(Color color)
{
	m_output << std::hex << static_cast<uint32_t>(color) << std::dec << std::endl;
}

void MockCanvas::DrawLine(const Point& from, const Point& to)
{
	m_output << from.x << "-" << from.y << " " << to.x << "-" << to.y << std::endl;
}

void MockCanvas::DrawEllipse(const Point& leftTop, float width, float height, size_t pointCount)
{
	m_output << leftTop.x << "-" << leftTop.y << "\nwidth: " << width << "\nheigth: " << height << "\npointCount: " << pointCount << std::endl;
}
