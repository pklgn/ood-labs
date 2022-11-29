// Console_Slides.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include "../Slides/Shape/SimpleShape/SimpleShape.h"
#include "../Slides/Shape/SimpleShape/Triangle/Triangle.h"
#include "../Slides/Shape/SimpleShape/Ellipse/Ellipse.h"
#include "../Slides/Shape/SimpleShape/Rectangle/Rectangle.h"
#include "../Slides/Canvas/ConsoleCanvas.h"
#include "../Slides/Shape/GroupShape/GroupShape.h"


int main()
{
	auto vertexA = Point{ 0, 1 };
	auto vertexB = Point{ 2, 3 };
	auto vertexC = Point{ 4, 5 };
	uint32_t fillcolor = 0xABCDEFFF;
	uint32_t linecolor = 0xFFFFFFFF;
	auto simpleLineStyle = std::make_shared<SimpleLineStyle>(linecolor);
	auto simpleFillStyle = std::make_shared<SimpleFillStyle>(fillcolor);
	auto triangle = std::make_shared<Triangle>(vertexA, vertexB, vertexC, simpleLineStyle, simpleFillStyle);

	auto canvas = ConsoleCanvas();
	triangle->Draw(canvas);

	std::cout << "=================\n";
	auto rectangleWidth = 100;
	auto rectangleHeight = 50;
	auto rectangle = std::make_shared<Rectangle>(vertexA, rectangleWidth, rectangleHeight, simpleLineStyle, simpleFillStyle);
	rectangle->Draw(canvas);

	std::cout << "=================\n";
	auto ellipseWidth = 200;
	auto ellipseHeight = 150;
	auto ellipse = std::make_shared<Ellipse>(vertexA, ellipseWidth, ellipseHeight, simpleLineStyle, simpleFillStyle);
	ellipse->Draw(canvas);

	std::vector<std::shared_ptr<IShape>> shapes{ triangle, rectangle, ellipse };
	auto group = GroupShape::Create(shapes);
	group->Draw(canvas);
}
