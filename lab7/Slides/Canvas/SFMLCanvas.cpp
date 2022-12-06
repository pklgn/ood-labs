#include "../pch.h"
#include "SFMLCanvas.h"

SFMLCanvas::SFMLCanvas(sf::RenderTarget& target)
	: m_renderTarget(target)
{
}

void SFMLCanvas::DrawLine(const Point& from, const Point& to)
{
	auto distanceX = to.x - from.x;
	auto distanceY = to.y - from.y;
	auto angle = atan2(distanceY, distanceX);

	auto cosAngle = cos(angle);
	auto width = (distanceX != 0)
		? distanceX / cosAngle
		: distanceY;

	sf::RectangleShape line(sf::Vector2f((float)std::abs(width), (float)m_lineThickness));
	line.setPosition((float)from.x, (float)from.y);
	line.setOutlineColor(m_fillColor);

	line.rotate((float)(angle * 180 / M_PI));

	m_renderTarget.draw(line);
}

void SFMLCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	auto ellipse = sf::CircleShape((float)width / 2);

	ellipse.setPosition((float)leftTop.x, (float)leftTop.y);
	ellipse.setScale(1, (float)(height / width));

	ellipse.setOutlineColor(m_lineColor);
	ellipse.setOutlineThickness((float)m_lineThickness);

	ellipse.setFillColor(sf::Color::Transparent);

	m_renderTarget.draw(ellipse);
}

void SFMLCanvas::FillEllipse(const Point& leftTop, double width, double height)
{
	auto ellipse = sf::CircleShape((float)width / 2);

	ellipse.setPosition((float)leftTop.x, (float)leftTop.y);
	ellipse.setScale(1, (float)(height / width));

	ellipse.setFillColor(m_fillColor);

	m_renderTarget.draw(ellipse);
}

void SFMLCanvas::FillPolygon(std::vector<Point>& points)
{
	sf::ConvexShape convex;

	auto pointCount = points.size();
	convex.setPointCount(pointCount);

	for (size_t index = 0; index < pointCount; ++index)
	{
		Point point = points[index];
		convex.setPoint(index, sf::Vector2f((float)point.x, (float)point.y));
	}

	convex.setFillColor(m_fillColor);
	//convex.setOutlineThickness((float)m_lineThickness);
	//convex.setOutlineColor(m_lineColor);

	m_renderTarget.draw(convex);
}

void SFMLCanvas::SetFillColor(uint32_t color)
{
	m_fillColor = sf::Color(color);
}

void SFMLCanvas::SetLineColor(uint32_t color)
{
	m_lineColor = sf::Color(color);
}

void SFMLCanvas::SetLineThickness(unsigned int thickness)
{
	m_lineThickness = thickness;
}

void SFMLCanvas::Capture(const std::string& outputFileName) const
{
	sf::Vector2u renderSize = m_renderTarget.getSize();
	sf::Texture texture;
	texture.create(renderSize.x, renderSize.y);
	
	try
	{
		sf::RenderWindow& window = dynamic_cast<sf::RenderWindow&>(m_renderTarget);
		texture.update(window);
		sf::Image screenshot = texture.copyToImage();
		screenshot.saveToFile(outputFileName);
	}
	catch (const std::bad_cast&)
	{
		throw std::runtime_error("Unable to capture canvas with not sf::RenderWindow render target type");
	}
}
