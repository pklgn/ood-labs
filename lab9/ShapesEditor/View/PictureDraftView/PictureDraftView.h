#pragma once
#include "../../App/PictureDraftAppModel/PictureDraftAppModel.h"
#include "../../App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../IView.h"
#include "../SelectionFrameView/SelectionFrameView.h"
#include "../ShapeView/ShapeView.h"
#include "IPictureDraftViewListener.h"

class PictureDraftView : public IView
{
public:
	void InsertSelectionFrame(ShapeAppModel&);
	void DeleteSelectionFrame();
	void Show(ICanvas&) override;
	void SetListener(IPictureDraftViewListener&);

private:
	std::vector<ShapeView> m_shapesView;
	std::vector<SelectionFrameView> m_selectionFrameViews;
	PictureDraftAppModel& m_pictureDraftAppModel;
	ShapeSelectionModel& m_shapeSelectionModel;
	IPictureDraftViewListener& m_listener;
};