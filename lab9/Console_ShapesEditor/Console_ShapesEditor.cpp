// Console_ShapesEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ShapesEditor/App/History/History.h"
#include "../ShapesEditor/App/PictureDraftAppModel/PictureDraftAppModel.h"
#include "../ShapesEditor/Model/PictureDraft/PictureDraft.h"
#include "../ShapesEditor/Model/Shape/Shape.h"
#include "../ShapesEditor/Model/Style/FillStyle/FillStyle.h"
#include "../ShapesEditor/Model/Style/LineStyle/LineStyle.h"
#include "../ShapesEditor/View/Canvas/SFML/SFMLCanvas.h"
#include "../ShapesEditor/View/MenuView/MenuView.h"
#include "../ShapesEditor/View/MenuView/MenuViewPresenter/MenuViewPresenter.h"
#include "../ShapesEditor/View/PictureDraftView/PictureDraftView.h"
#include "../ShapesEditor/View/PictureDraftView/PictureDraftViewPresenter/PictureDraftViewPresenter.h"

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
	auto pictureDraft = std::make_shared<PictureDraft>();
	pictureDraft->InsertShape(BuildRocketShape(), 0);
	RectD frame = { -10,
		150,
		300,
		200 };
	pictureDraft->InsertShape(std::make_shared<Shape>(ShapeType::Triangle, frame), 1);
	auto history = std::make_shared<History>();

	PictureDraftAppModel pictureDraftAppModel(pictureDraft, history);
	ShapeSelectionModel shapeSelectionModel(history);
	PictureDraftView pictureDraftView(pictureDraftAppModel, shapeSelectionModel, 800, 600);
	auto pictureDraftViewPresenter = std::make_shared<PictureDraftViewPresenter>(shapeSelectionModel, pictureDraftView, pictureDraftAppModel, *history);
	size_t menuHeight = 100;
	MenuView menuView(800, menuHeight, 600);
	MenuViewPresenter menuViewPresenter(menuView, *pictureDraftViewPresenter);
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	auto renderWindow = sf::RenderWindow(sf::VideoMode(800, 700), "ShapesEditor", sf::Style::Default, settings);
	auto sfmlCanvas = SFMLCanvas(renderWindow);

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
				renderWindow.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				Point point = { (double)event.mouseButton.x, (double)event.mouseButton.y };
				if (!isDragging)
				{
					clickPoint = point;
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					pictureDraftViewPresenter->OnMouseDown(point);

					if (600 < point.y && point.y <= 700 )
					{
						point.y -= 600;
						menuViewPresenter.OnMouseDown(point);
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asMilliseconds() >= 100)
			{
				auto point = sf::Mouse::getPosition(renderWindow);
				Point offset = { point.x - clickPoint.x, point.y - clickPoint.y };
				isDragging = true;
			}
			else
			{
				clock.restart();
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				Point point = { (double)event.mouseButton.x, (double)event.mouseButton.y };
				pictureDraftViewPresenter->OnMouseUp(point);
				isDragging = false;
			}
			if (isDragging && event.type == sf::Event::MouseLeft)
			{
				Point point = { (double)event.mouseButton.x, (double)event.mouseButton.y };
				pictureDraftViewPresenter->OnMouseUp(point);
				pictureDraftViewPresenter->OnMouseDown({ -1, -1 });
			}
		}

		// clear the window with black color
		renderWindow.clear(sf::Color::White);

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
		menuView.Show(sfmlCanvas);

		// end the current frame
		renderWindow.display();
	}

	return 0;
}
