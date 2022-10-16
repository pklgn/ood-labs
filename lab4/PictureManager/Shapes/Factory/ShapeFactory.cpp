#include "../../pch.h"
#include <algorithm>
#include <cctype>

#include "ShapeFactory.h"
#include "../Ellipse.h"
#include "../Rectangle.h"
#include "../RegularPolygon.h"
#include "../Triangle.h"

Color GetColorFrom(const std::string& str);
std::string ToLower(const std::string& str);
ShapePtr CreateEllipse(std::stringstream& ss);
ShapePtr CreateRectangle(std::stringstream& ss);
ShapePtr CreateRegularPolygon(std::stringstream& ss);
ShapePtr CreateTriangle(std::stringstream& ss);

ShapePtr ShapeFactory::CreateShape(const std::string& description)
{
	std::stringstream ss(description);
	std::string shapeName;
	ss >> shapeName;
	auto lowerShapeName = ToLower(shapeName);

	if (lowerShapeName == "ellipse")
	{
		return CreateEllipse(ss);
	}

	if (lowerShapeName == "rectangle")
	{
		return CreateRectangle(ss);
	}

	if (lowerShapeName == "regular-polygon")
	{
		return CreateRegularPolygon(ss);
	}

	if (lowerShapeName == "triangle")
	{
		return CreateTriangle(ss);
	}

	return nullptr;
}

ShapePtr CreateEllipse(std::stringstream& ss)
{
	Point center;
	float horizontalRadius;
	float verticalRaduis;
	std::string colorStr;

	ss >> center >> horizontalRadius >> verticalRaduis >> colorStr;

	if (ss.fail() ||
		verticalRaduis < 0 ||
		horizontalRadius < 0)
	{
		return nullptr;
	}

	Point leftTop = { center.x - horizontalRadius, center.y - verticalRaduis };

	return std::make_unique<Ellipse>(leftTop, horizontalRadius, verticalRaduis, GetColorFrom(colorStr));
}

ShapePtr CreateRectangle(std::stringstream& ss)
{
	Point leftTop;
	Point rightBottom;
	std::string colorStr;

	ss >> leftTop >> rightBottom >> colorStr;

	if (ss.fail())
	{
		return nullptr;
	}

	return std::make_unique<Rectangle>(leftTop, rightBottom, GetColorFrom(colorStr));
}

ShapePtr CreateRegularPolygon(std::stringstream& ss)
{
	Point center;
	size_t vertexCount;
	float radius;
	std::string colorStr;

	ss >> center >> vertexCount >> radius >> colorStr;

	if (ss.fail() ||
		radius < 0)
	{
		return nullptr;
	}

	return std::make_unique<RegularPolygon>(center, vertexCount, radius, GetColorFrom(colorStr));
}

ShapePtr CreateTriangle(std::stringstream& ss)
{
	Point vertex1;
	Point vertex2;
	Point vertex3;
	std::string colorStr;

	ss >> vertex1 >> vertex2 >> vertex3 >> colorStr;

	if (ss.fail())
	{
		return nullptr;
	}

	return std::make_unique<Triangle>(vertex1, vertex2, vertex3, GetColorFrom(colorStr));
}

std::string ToLower(const std::string& str)
{
	std::string result = str;
	std::transform(str.begin(), str.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });

	return result;
}

Color GetColorFrom(const std::string& str)
{
	auto lowerStr = ToLower(str);

	if (str == "green")
	{
		return Color::Green;
	}
	
	if (str == "red")
	{
		return Color::Red;
	}
	
	if (str == "blue")
	{
		return Color::Blue;
	}
	
	if (str == "yellow")
	{
		return Color::Yellow;
	}
	if (str == "pink")
	{
		return Color::Pink;
	}

	return Color::Black;
}