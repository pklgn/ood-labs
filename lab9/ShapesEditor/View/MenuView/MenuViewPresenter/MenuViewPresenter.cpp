#include "../../../pch.h"
#include "MenuViewPresenter.h"

MenuViewPresenter::MenuViewPresenter(MenuView& menuView, PictureDraftViewPresenter& pictureDraftViewPresenter)
	: m_menuView(menuView)
	, m_pictureDraftViewPresenter(pictureDraftViewPresenter)
{
}

void MenuViewPresenter::OnMouseDown(const Point& point)
{
	auto width = m_menuView.GetWidth();
	auto height = m_menuView.GetHeight();
	if (point.x < width / 6)
	{
		m_pictureDraftViewPresenter.InsertShape(ShapeType::Triangle);
	}
	else if (width / 6 <= point.x && point.x < width * 2/6)
	{
		m_pictureDraftViewPresenter.InsertShape(ShapeType::Rectangle);
	}
	else if (width * 2/6 <= point.x && point.x < width * 3/6)
	{
		m_pictureDraftViewPresenter.InsertShape(ShapeType::Ellipse);
	}
	else if (width * 3/6 <= point.x && point.x < width * 4/6)
	{
		m_pictureDraftViewPresenter.DeleteShape();
	}
	else if (width * 4/6 <= point.x && point.x < width * 5/6)
	{
		m_pictureDraftViewPresenter.Undo();
	}
	else if (width * 5/6 <= point.x && point.x < width)
	{
		m_pictureDraftViewPresenter.Redo();
	}
}
