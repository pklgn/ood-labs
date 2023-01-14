#pragma once
#include "../IPictureDraftViewListener.h"
#include "../../../App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../PictureDraftView.h"

class PictureDraftViewPresenter : public IPictureDraftViewListener
{
public:
	void OnMouseDown(const Point&) override;
	void OnMouseUp(const Point&) override;

private:
	ShapeSelectionModel& m_shapeSelectionModel;
	PictureDraftView& m_pictureDraftView;
};
