#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

const unsigned int DEFAULT_CANVAS_LINE_THICKNESS = 1;

class SFMLCanvas : public ICanvas
{
public:
	SFMLCanvas(sf::RenderTarget&);

	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(const Point& leftTop, double width, double height) override;
	void FillEllipse(const Point& leftTop, double width, double height) override;
	void FillPolygon(std::vector<Point>&) override;
	void SetFillColor(uint32_t) override;
	void SetLineColor(uint32_t) override;
	void SetLineThickness(unsigned int) override;

	void CaptureShapes(const std::string& outputFileName);

private:
	sf::Color m_lineColor = sf::Color::White;
	sf::Color m_fillColor = sf::Color::Black;
	unsigned int m_lineThickness = DEFAULT_CANVAS_LINE_THICKNESS;
	sf::RenderTarget& m_renderTarget;
};