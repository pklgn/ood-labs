#pragma once

enum class ShapeType
{
	Rectangle,
	Triangle,
	Ellipse,
};

inline std::string ShapeTypeToString(ShapeType type)
{
	switch (type)
	{
	case ShapeType::Rectangle:
		return "Rectangle";
	case ShapeType::Triangle:
		return "Triangle";
	case ShapeType::Ellipse:
		return "Ellipse";
	default:
		break;
	}
}