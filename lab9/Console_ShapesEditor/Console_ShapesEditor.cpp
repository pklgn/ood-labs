// Console_ShapesEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ShapesEditor/Model/PictureDraft/PictureDraft.h"
#include "../ShapesEditor/Model/Shape/Shape.h"
#include "../ShapesEditor/Model/Style/FillStyle/FillStyle.h"
#include "../ShapesEditor/Model/Style/LineStyle/LineStyle.h"
#include "../ShapesEditor/App/History/History.h"
#include "../ShapesEditor/App/PictureDraftAppModel/PictureDraftAppModel.h"
#include "../ShapesEditor/View/PictureDraftView/PictureDraftView.h"
#include "../ShapesEditor/View/PictureDraftView/PictureDraftViewPresenter/PictureDraftViewPresenter.h"
#include "../ShapesEditor/View/Canvas/SFML/SFMLCanvas.h"

std::shared_ptr<Shape> BuildRocketShape()
{
	RectD frame = { 150,
		150,
		300,
		200 };
	return std::make_shared<Shape>(ShapeType::Rectangle, frame);
}


int main()
{
    std::cout << "Hello World!\n";
	auto pictureDraft = std::make_shared<PictureDraft>();
	pictureDraft->InsertShape(BuildRocketShape(), 0);
	auto history = std::make_shared<History>();

	PictureDraftAppModel pictureDraftAppModel(pictureDraft, history);
	ShapeSelectionModel shapeSelectionModel;
	PictureDraftView pictureDraftView(pictureDraftAppModel, shapeSelectionModel);
	auto pictureDraftViewPresenter = std::make_shared<PictureDraftViewPresenter>(shapeSelectionModel, pictureDraftView, pictureDraftAppModel);
	//pictureDraftView.SetListener(pictureDraftViewPresenter);

	//sf::ContextSettings settings;
	//settings.antialiasingLevel = 8;
	auto renderWindow = sf::RenderWindow(sf::VideoMode(800, 600), "ShapesEditor");
	auto sfmlCanvas = SFMLCanvas(renderWindow);
	//renderWindow.setFramerateLimit(30);

	// run the program as long as the window is open
	bool isDragging = false;
	sf::Clock clock;
	Point clickPoint;
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
			if (event.type == sf::Event::MouseButtonPressed)
			{
				Point point = { event.mouseButton.x, event.mouseButton.y };
				if (!isDragging)
				{
					clickPoint = point;
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					pictureDraftViewPresenter->OnMouseDown(point);
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asMilliseconds() >= 100)
			{
				auto point = sf::Mouse::getPosition(renderWindow);
				Point offset = { point.x - clickPoint.x, point.y - clickPoint.y };
				//std::cout << "==========================" << clock.getElapsedTime().asMilliseconds() << "\n";
				//std::cout << "offset    " << offset << std::endl;
				//std::cout << "clickPoint" << clickPoint << std::endl;
				//std::cout << "point     " << point.x << " " << point.y << std::endl;
				isDragging = true;
			}
			else
			{
				clock.restart();
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				isDragging = false;
			}

		}

		// clear the window with black color
		renderWindow.clear(sf::Color::Black);

		// window.draw(...);
		if (isDragging)
		{
			auto point = sf::Mouse::getPosition(renderWindow);
			Point offset = { point.x - clickPoint.x, point.y - clickPoint.y };
			pictureDraftViewPresenter->OnDrag(offset, clickPoint);
			clickPoint.x += offset.x;
			clickPoint.y += offset.y;
		}
		pictureDraftView.Show(sfmlCanvas);

		// end the current frame
		renderWindow.display();
	}

	return 0;
}
