#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class SFMLCanvas : public ICanvas
{
public:
	SFMLCanvas(sf::RenderTarget&);

	void DrawLine(const Point& from, const Point& to) override;
	void DrawClosedPolyLine(std::vector<Point>&) override;
	void DrawEllipse(const Point& leftTop, double width, double height) override;
	void FillEllipse(const Point& leftTop, double width, double height) override;
	void FillPolygon(std::vector<Point>&) override;
	void SetFillColor(uint32_t) override;
	void SetLineColor(uint32_t) override;
	void SetLineThickness(unsigned int) override;

	void Capture(const std::string& outputFileName) const;

private:
	void DrawClosedPolyLineSegment(size_t index, const std::vector<Point>& points);

	sf::Color m_lineColor;
	sf::Color m_fillColor;
	unsigned int m_lineThickness;
	sf::RenderTarget& m_renderTarget;
};