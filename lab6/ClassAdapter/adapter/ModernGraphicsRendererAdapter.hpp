#pragma once

#include "../graphics_lib/graphics_lib.hpp"
#include "../modern_graphics_lib/modern_graphics_lib.hpp"

const modern_graphics_lib::Point DEFAULT_POINT{ 0, 0 };

class ModernGraphicsRendererAdapter : public graphics_lib::ICanvas, private modern_graphics_lib::ModernGraphicsRenderer
{
public:
	ModernGraphicsRendererAdapter(std::ostream& output)
		: modern_graphics_lib::ModernGraphicsRenderer(output)
		, m_startPoint(DEFAULT_POINT.x, DEFAULT_POINT.y)
	{
		BeginDraw();
	}

	~ModernGraphicsRendererAdapter()
	{
		if (IsDrawing())
		{
			EndDraw();
		}
	}

	void MoveTo(int x, int y) override
	{
		SetStartPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		DrawLine(m_startPoint, modern_graphics_lib::Point(x, y));
	}

private:
	void SetStartPoint(int x, int y)
	{
		m_startPoint.x = x;
		m_startPoint.y = y;
	}

	modern_graphics_lib::Point m_startPoint;
};