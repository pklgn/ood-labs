#pragma once
#include <ostream>
#include "..\PictureManager\Canvas\ICanvas.h"

class MockCanvas : public ICanvas
{
public:
	MockCanvas(std::ostream&);

	void SetColor(Color) override;
	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(const Point& leftTop, float width, float height, size_t pointCount = ELLIPSE_POINT_COUNT) override;

private:
	std::ostream& m_output;
};
