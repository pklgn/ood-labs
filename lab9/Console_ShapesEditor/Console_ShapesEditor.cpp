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


int main()
{
	// Document
	auto pictureDraft = std::make_shared<PictureDraft>();
	auto history = std::make_shared<History>();

	PictureDraftAppModel pictureDraftAppModel(pictureDraft, history);
	ShapeSelectionModel shapeSelectionModel(history);

	// Edit window
	Point pictureDraftSize = { 800, 600 };
	PictureDraftView pictureDraftView(pictureDraftAppModel, shapeSelectionModel, pictureDraftSize.x, pictureDraftSize.y);
	auto pictureDraftViewPresenter = std::make_shared<PictureDraftViewPresenter>(shapeSelectionModel, pictureDraftView, pictureDraftAppModel, *history);

	Point menuSize = { 800, 100 };
	MenuView menuView(menuSize.x, menuSize.y, pictureDraftSize.y);
	MenuViewPresenter menuViewPresenter(menuView, *pictureDraftViewPresenter);
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	auto renderWindow = sf::RenderWindow(sf::VideoMode(pictureDraftSize.x, pictureDraftSize.y + menuSize.y), "ShapesEditor", sf::Style::Default, settings);
	auto sfmlCanvas = SFMLCanvas(renderWindow);

	// run the program as long as the window is open
	bool isDragging = false;
	Point clickPoint;
	sf::Clock clock;
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
					if (pictureDraftSize.y < point.y && point.y <= pictureDraftSize.y + menuSize.y)
					{
						point.y -= pictureDraftSize.y;
						menuViewPresenter.OnMouseDown(point);
					}
					else
					{
						pictureDraftViewPresenter->OnMouseDown(point);
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asMilliseconds() >= 100)
			{
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
		if (isDragging)
		{
			auto point = sf::Mouse::getPosition(renderWindow);
			Point offset = { point.x - clickPoint.x, point.y - clickPoint.y };
			pictureDraftViewPresenter->OnDrag(offset, clickPoint);
			clickPoint.x += offset.x;
			clickPoint.y += offset.y;
		}

		// clear the window with black color
		renderWindow.clear(sf::Color::White);

		// window.draw(...);
		pictureDraftView.Show(sfmlCanvas);
		menuView.Show(sfmlCanvas);

		// end the current frame
		renderWindow.display();
	}

	return 0;
}
