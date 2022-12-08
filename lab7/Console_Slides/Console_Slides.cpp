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

std::shared_ptr<IShape> BuildRocketShape()
{
	auto bodyLineStyle = std::make_shared<SimpleLineStyle>(0xFFFFFFFF, 3);
	auto bodyFillStyle = std::make_shared<SimpleFillStyle>(0xccccccFF);
	auto body = std::make_shared<Rectangle>(Point{ 150, 150 }, 300, 200, bodyLineStyle, bodyFillStyle);

	auto fairingLineStyle = std::make_shared<SimpleLineStyle>(0x32A5CBFF, 4);
	auto fairingFillStyle = std::make_shared<SimpleFillStyle>(0xFFFFFFFF);
	auto fairing = std::make_shared<Triangle>(Point{ 450, 148 }, Point{ 600, 250 }, Point{ 450, 350 }, fairingLineStyle);

	auto portholeLineStyle = std::make_shared<SimpleLineStyle>(0x32A5CBFF, 3);
	auto portholeFillStyle = std::make_shared<SimpleFillStyle>(0x4DB4F0FF);
	auto porthole = std::make_shared<Ellipse>(Point{300, 200}, 100, 100, portholeLineStyle, portholeFillStyle);

	auto bigFlameLineStyle = std::make_shared<SimpleLineStyle>(0xEF2F2FFF, 1);
	auto bigFlameFillStyle = std::make_shared<SimpleFillStyle>(0xF7C707FF);
	auto bigFlame = std::make_shared<Triangle>(Point{ 150, 175 }, Point{ 150, 325 }, Point{ 50, 250 }, bigFlameLineStyle, bigFlameFillStyle);

	auto littleFlameLineStyle = std::make_shared<SimpleLineStyle>(0xF7DD78FF, 2);
	auto littleFlameFillStyle = std::make_shared<SimpleFillStyle>(0xBF5700FF);
	auto littleFlame = std::make_shared<Triangle>(Point{ 150, 200 }, Point{ 150, 300 }, Point{ 100, 250 }, littleFlameLineStyle, littleFlameFillStyle);

	auto tailPartLineStyle = std::make_shared<SimpleLineStyle>(0x739A69FF, 2);
	auto tailPartFillStyle = std::make_shared<SimpleFillStyle>(0x165806FF);
	auto tailPart1 = std::make_shared<Triangle>(Point{ 150, 150 }, Point{ 150, 50 }, Point{ 250, 150 }, tailPartLineStyle, tailPartFillStyle);
	auto tailPart2 = std::make_shared<Triangle>(Point{ 150, 450 }, Point{ 150, 350 }, Point{ 250, 350 }, tailPartLineStyle, tailPartFillStyle);

	std::vector<std::shared_ptr<IShape>> parts{ body, fairing, porthole, bigFlame, littleFlame, tailPart1, tailPart2 };
	
	return GroupShape::Create(parts);
}

int main()
{
	auto rocketShape = BuildRocketShape(); 
	auto farRocketShape = BuildRocketShape();
	auto farRocketShapeFrame = farRocketShape->GetFrame();
	farRocketShapeFrame = {
		farRocketShapeFrame.left += 450,
		farRocketShapeFrame.top += 300,
		farRocketShapeFrame.width /= 2,
		farRocketShapeFrame.height /= 2,
	};
	farRocketShape->SetFrame(farRocketShapeFrame);

	auto slide = std::make_shared<Slide>();

	//add group
	slide->InsertShape(rocketShape, 0);
	slide->InsertShape(farRocketShape, 1);
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	auto renderWindow = sf::RenderWindow(sf::VideoMode(800, 600), "rockets", sf::Style::Default, settings);
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
				sfmlCanvas.Capture("ROCKETS.JPG");
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
