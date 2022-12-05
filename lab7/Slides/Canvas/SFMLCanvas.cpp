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

	sf::RectangleShape line(sf::Vector2f(std::abs(width), m_lineThickness));
	line.setPosition(from.x, from.y);
	line.setOutlineColor(m_fillColor);

	line.rotate(angle * 180 / M_PI);

	m_renderTarget.draw(line);
}

void SFMLCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	auto ellipse = sf::CircleShape(width / 2);

	ellipse.setPosition(leftTop.x, leftTop.y);
	ellipse.setScale(1, height / width);

	ellipse.setOutlineColor(m_lineColor);
	ellipse.setOutlineThickness(m_lineThickness);

	ellipse.setFillColor(sf::Color::Transparent);

	m_renderTarget.draw(ellipse);
}

void SFMLCanvas::FillEllipse(const Point& leftTop, double width, double height)
{
	auto ellipse = sf::CircleShape(width / 2);

	ellipse.setPosition(leftTop.x, leftTop.y);
	ellipse.setScale(1, height / width);

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
		convex.setPoint(index, sf::Vector2f(point.x, point.y));
	}

	convex.setFillColor(m_fillColor);
	convex.setOutlineThickness(m_lineThickness);
	convex.setOutlineColor(sf::Color::Transparent);

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

void SFMLCanvas::CaptureShapes(const std::string& outputFileName)
{
	sf::Vector2u windowSize = m_renderTarget.getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	auto& window = static_cast<sf::RenderWindow&>(m_renderTarget);
	texture.update(window);
	sf::Image screenshot = texture.copyToImage();
	screenshot.saveToFile(outputFileName);
}
