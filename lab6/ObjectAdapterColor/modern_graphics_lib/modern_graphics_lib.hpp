#pragma once
#include <ios>
#include <format>
#include <iostream>

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
class Point
{
public:
	Point(int x, int y)
		: x(x)
		, y(y)
	{
	}

	int x;
	int y;
};

// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
class RGBAColor
{
public:
	RGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
		CheckColorComponent(r);
		CheckColorComponent(g);
		CheckColorComponent(b);
		CheckColorComponent(a);
	}
	float r, g, b, a;

private:
	void CheckColorComponent(float component)
	{
		if (component < 0.0f ||
			component > 1.0f)
		{
			throw std::invalid_argument("Invalid color component value");
		}
	}
};


// Класс для современного рисования графики
class ModernGraphicsRenderer
{
public:
	ModernGraphicsRenderer(std::ostream& strm)
		: m_out(strm)
	{
	}

	~ModernGraphicsRenderer()
	{
		if (m_drawing) // Завершаем рисование, если оно было начато
		{
			EndDraw();
		}
	}

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw()
	{
		if (m_drawing)
		{
			throw std::logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << std::endl;
		m_drawing = true;
	}

	// Выполняет рисование линии
	void DrawLine(const Point& start, const Point& end, const RGBAColor& color)
	{
		if (!m_drawing)
		{
			throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << std::format(R"(  <line fromX="{}" fromY="{}" toX="{}" toY="{}">)", start.x, start.y, end.x, end.y)
			  << std::endl
			  << std::format(R"(    <color r="{:.2f}" g="{:.2f}" b="{:.2f}" a="{:.2f}" />)", color.r, color.g, color.b, color.a)
			  << "\n  </line>"
			  << std::endl;
	}

	// Этот метод должен быть вызван в конце рисования
	void EndDraw()
	{
		if (!m_drawing)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << std::endl;
		m_drawing = false;
	}

	bool IsDrawing()
	{
		return m_drawing;
	}

private:
	std::ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib
