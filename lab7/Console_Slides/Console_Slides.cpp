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
	auto vertexA = Point{ 30, 400 };
	auto vertexB = Point{ 300, 200 };
	auto vertexC = Point{ 700, 500 };
	uint32_t fillcolor = 0x00D678FF;
	uint32_t linecolor = 0xFFFFFFFF;

	auto simpleLineStyle = std::make_shared<SimpleLineStyle>(linecolor, 10);
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
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	auto renderWindow = sf::RenderWindow(sf::VideoMode(800, 600), "canvas", sf::Style::Default, settings);
	auto sfmlCanvas = SFMLCanvas(renderWindow);

	// run the program as long as the window is open
	while (renderWindow.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				sfmlCanvas.Capture("OUTPUT.JPG");
				renderWindow.close();
			}
		}

		// clear the window with black color
		renderWindow.clear(sf::Color::Black);

		// window.draw(...);
		slide->Draw(sfmlCanvas);

		// end the current frame
		renderWindow.display();
	}

	slide->Draw(sfmlCanvas);
}