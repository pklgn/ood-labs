#pragma once
#include "../IMenuViewListener.h"
#include "../MenuView.h"
#include "../../PictureDraftView/PictureDraftViewPresenter/PictureDraftViewPresenter.h"

class MenuViewPresenter : public IMenuViewListener
{
public:
	MenuViewPresenter(MenuView&, PictureDraftViewPresenter&);

	void OnMouseDown(const Point&) override;

private:
	MenuView& m_menuView;
	PictureDraftViewPresenter& m_pictureDraftViewPresenter;
};