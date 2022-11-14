﻿#pragma once
#include "../graphics_lib/graphics_lib.hpp"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;

	virtual ~ICanvasDrawable() = default;
};

class Triangle : public ICanvasDrawable
{
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color = 0x000000)
		: m_point1(p1)
		, m_point2(p2)
		, m_point3(p3)
		, m_color(color)
	{
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);
		canvas.MoveTo(m_point1.x, m_point1.y);
		canvas.LineTo(m_point2.x, m_point2.y);
		canvas.MoveTo(m_point2.x, m_point2.y);
		canvas.LineTo(m_point3.x, m_point3.y);
		canvas.MoveTo(m_point3.x, m_point3.y);
		canvas.LineTo(m_point1.x, m_point1.y);
	}

private:
	Point m_point1;
	Point m_point2;
	Point m_point3;
	uint32_t m_color;
};

class Rectangle : public ICanvasDrawable
{
public:
	Rectangle(const Point& leftTop, int width, int height, uint32_t color = 0x000000)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
		, m_color(color)
	{
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.MoveTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

private:
	Point m_leftTop;
	int m_width;
	int m_height;
	uint32_t m_color;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CanvasPainter
{
public:
	CanvasPainter(graphics_lib::ICanvas& canvas)
		: m_canvas(canvas)
	{
	}
	void Draw(const ICanvasDrawable& drawable)
	{
		drawable.Draw(m_canvas);
	}

private:
	graphics_lib::ICanvas& m_canvas;
};
} // namespace shape_drawing_lib
