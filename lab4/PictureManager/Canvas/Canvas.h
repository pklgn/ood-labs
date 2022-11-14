#pragma once

#include "ICanvas.h"
#include <SFML\Graphics.hpp>

class Canvas : public ICanvas
{
public:
	Canvas(unsigned width, unsigned height, const std::string& windowTitle);

	void SetColor(Color) override;
	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(const Point& center, float width, float height, size_t pointCount) override;
	
	void CaptureShapes(const std::string& outputFileName);

private:
	Color m_color;
	sf::RenderWindow m_renderWindow;
};