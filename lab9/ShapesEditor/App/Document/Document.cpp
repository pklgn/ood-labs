#include "../../pch.h"
#include <SFML/Graphics.hpp>
#include "../../common/Point/Point.h"
#include "../../View/Canvas/SFML/SFMLCanvas.h"
#include "../../View/MenuView/MenuView.h"
#include "../../View/MenuView/MenuViewPresenter/MenuViewPresenter.h"
#include "../../View/PictureDraftView/PictureDraftView.h"
#include "../../View/PictureDraftView/PictureDraftViewPresenter/PictureDraftViewPresenter.h"
#include "../PictureDraftAppModel/PictureDraftAppModel.h"
#include "../ShapeSelectionModel/ShapeSelectionModel.h"
#include "../UseCases/UseCaseFactory/UseCaseFactory.h"
#include "Document.h"

Document::Document()
{
	m_pictureDraft = std::make_shared<PictureDraft>();
	m_commandsHistory = std::make_shared<CommandsHistory>();
}

void Document::Run()
{
	InitEditWindow();
}

void Document::InitEditWindow()
{
	PictureDraftAppModel pictureDraftAppModel(m_pictureDraft, m_commandsHistory);
	ShapeSelectionModel shapeSelectionModel;

	// Edit window
	Point pictureDraftSize = { 800, 600 };
	PictureDraftView pictureDraftView(pictureDraftAppModel, shapeSelectionModel, (size_t)pictureDraftSize.x, (size_t)pictureDraftSize.y);
	auto useCaseFactory = UseCaseFactory(shapeSelectionModel, *m_commandsHistory);
	auto pictureDraftViewPresenter = std::make_shared<PictureDraftViewPresenter>(shapeSelectionModel, pictureDraftView, pictureDraftAppModel, useCaseFactory);

	Point menuSize = { 800, 100 };
	MenuView menuView((size_t)menuSize.x, (size_t)menuSize.y, (size_t)pictureDraftSize.y);
	MenuViewPresenter menuViewPresenter(menuView, *pictureDraftViewPresenter);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	auto renderWindow = sf::RenderWindow(sf::VideoMode((unsigned int)pictureDraftSize.x, (unsigned int)(pictureDraftSize.y + menuSize.y)), "ShapesEditor", sf::Style::Default, settings);
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
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Delete)
				{
					pictureDraftViewPresenter->DeleteShape();
				}
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
}