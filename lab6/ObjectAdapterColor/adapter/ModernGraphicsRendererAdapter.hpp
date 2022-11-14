#pragma once
#include "../graphics_lib/graphics_lib.hpp"
#include "../modern_graphics_lib/modern_graphics_lib.hpp"

const modern_graphics_lib::Point DEFAULT_POINT{ 0, 0 };
const modern_graphics_lib::RGBAColor DEFAULT_COLOR{ 0, 0, 0, 1 };

class ModernGraphicsRendererAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphicsRendererAdapter(modern_graphics_lib::ModernGraphicsRenderer& adaptee)
		: m_renderer(adaptee)
		, m_startPoint(DEFAULT_POINT.x, DEFAULT_POINT.y)
		, m_color(DEFAULT_COLOR.r, DEFAULT_COLOR.g, DEFAULT_COLOR.g, DEFAULT_COLOR.a)
	{
		m_renderer.BeginDraw();
	}

	~ModernGraphicsRendererAdapter()
	{
		if (m_renderer.IsDrawing())
		{
			m_renderer.EndDraw();
		}
	}

	void SetColor(uint32_t rgbColor) override
	{
		m_color.r = float((rgbColor >> 16) & 0xFF) / 0xFF;
		m_color.g = float((rgbColor >> 8) & 0xFF) / 0xFF;
		m_color.b = float(rgbColor & 0xFF) / 0xFF; 
	}

	void MoveTo(int x, int y) override
	{
		SetStartPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		m_renderer.DrawLine(m_startPoint, modern_graphics_lib::Point(x, y), m_color);
	}

private:
	void SetStartPoint(int x, int y)
	{
		m_startPoint.x = x;
		m_startPoint.y = y;
	}

	modern_graphics_lib::Point m_startPoint;
	modern_graphics_lib::ModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::RGBAColor m_color;
};