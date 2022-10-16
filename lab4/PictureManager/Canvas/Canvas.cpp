#include "../pch.h"
#include "Canvas.h"

Canvas::Canvas(unsigned width, unsigned height, const std::string& windowTitle)
	: m_color(Color::Black)
	, m_renderWindow(sf::VideoMode(width, height), windowTitle)
{
}

void Canvas::SetColor(Color color)
{
	m_color = color;
}

void Canvas::DrawLine(const Point& from, const Point& to)
{
	auto colorWithoutOpacity = static_cast<uint32_t>(m_color);
	auto colorWithOpacity = colorWithoutOpacity << 8;
	sf::Color color(colorWithOpacity);
	color.a = 0xff;

	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(from.x, from.y), color),
		sf::Vertex(sf::Vector2f(to.x, to.y), color)
	};

	m_renderWindow.draw(line, 2, sf::Lines);
}

void Canvas::DrawEllipse(const Point& center, float width, float height, size_t pointCount)
{
	auto ellipse = sf::CircleShape(width / 2, pointCount);

	ellipse.setPosition(center.x + width / 2, center.y - height / 2);
	ellipse.setScale(1, height / width);

	auto colorWithoutOpacity = static_cast<uint32_t>(m_color);
	auto colorWithOpacity = colorWithoutOpacity << 8;
	sf::Color outlineColor(colorWithOpacity);
	outlineColor.a = 0xff;

	ellipse.setFillColor(sf::Color::Black);
	ellipse.setOutlineColor(outlineColor);
	ellipse.setOutlineThickness(1);

	m_renderWindow.draw(ellipse);
}

void Canvas::CaptureShapes(const std::string& outputFileName)
{
	sf::Vector2u windowSize = m_renderWindow.getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	texture.update(m_renderWindow);
	sf::Image screenshot = texture.copyToImage();
	screenshot.saveToFile(outputFileName);
}
