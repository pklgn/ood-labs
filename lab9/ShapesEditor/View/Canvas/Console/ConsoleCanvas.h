#pragma once
#include "../ICanvas.h"

class ConsoleCanvas : public ICanvas
{
public:
	ConsoleCanvas(std::ostream&);

	void DrawLine(const Point& from, const Point& to) override;
	void DrawClosedPolyLine(const std::vector<Point>&) override;
	void DrawEllipse(const Point& leftTop, double width, double height) override;
	void FillEllipse(const Point& leftTop, double width, double height) override;
	void FillPolygon(const std::vector<Point>&) override;
	void SetFillColor(uint32_t) override;
	void SetLineColor(uint32_t) override;
	void SetLineThickness(unsigned int) override;

private:
	uint32_t m_lineColor;
	uint32_t m_fillColor;
	unsigned int m_lineThickness;
	std::ostream& m_output;
};
