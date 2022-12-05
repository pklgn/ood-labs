// Console_Slides.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "../Slides/Shape/SimpleShape/SimpleShape.h"
#include "../Slides/Shape/SimpleShape/Triangle/Triangle.h"
#include "../Slides/Shape/SimpleShape/Ellipse/Ellipse.h"
#include "../Slides/Shape/SimpleShape/Rectangle/Rectangle.h"
#include "../Slides/Canvas/ConsoleCanvas.h"
#include "../Slides/Shape/GroupShape/GroupShape.h"
#include "../Slides/Canvas/SFMLCanvas.h"
#include "../Slides/Slide/Slide.h"


int main()
{
	auto vertexA = Point{ 0, 600 };
	auto vertexB = Point{ 300, 200 };
	auto vertexC = Point{ 800, 500 };
	uint32_t fillcolor = 0x00D678FF;
	uint32_t linecolor = 0xFFFFFFFF;

	auto simpleLineStyle = std::make_shared<SimpleLineStyle>(linecolor);
	auto simpleFillStyle = std::make_shared<SimpleFillStyle>(fillcolor);
	auto triangle = std::make_shared<Triangle>(vertexA, vertexB, vertexC, simpleLineStyle, simpleFillStyle);

	auto consoleCanvas = ConsoleCanvas();
	triangle->Draw(consoleCanvas);
	std::cout << "=================\n";

	auto rectangleWidth = 400;
	auto rectangleHeight = 300;
	auto rectangle = std::make_shared<Rectangle>(Point{70, 80}, rectangleWidth, rectangleHeight, simpleLineStyle, simpleFillStyle);

	rectangle->Draw(consoleCanvas);
	std::cout << "=================\n";

	auto ellipseWidth = 300;
	auto ellipseHeight = 200;
	auto ellipse = std::make_shared<Ellipse>(Point{0, 0}, ellipseWidth, ellipseHeight, simpleLineStyle, simpleFillStyle);
	ellipse->Draw(consoleCanvas);

	std::vector<std::shared_ptr<IShape>> shapes{ triangle, rectangle, ellipse };
	auto group = GroupShape::Create(shapes);
	//group->Draw(sfmlCanvas);
	//sfmlCanvas.CaptureShapes("kartina-maslom.jpg");

	auto slide = std::make_shared<Slide>();
	//add several shapes independently
	//slide->InsertShape(triangle, 0);
	//slide->InsertShape(rectangle, 1);
	//slide->InsertShape(ellipse, 2);

	//add group
	slide->InsertShape(group, 0);
	
	//change frame
	//auto shape = slide->GetShapeAtIndex(0);
	//shape->SetFrame({ 0, 0, 400, 300 });

	auto renderTarget = sf::RenderWindow(sf::VideoMode(800, 600), "canvas");
	auto sfmlCanvas = SFMLCanvas(renderTarget);

	slide->Draw(sfmlCanvas);
	sfmlCanvas.CaptureShapes("OUTPUT.JPG");
}
