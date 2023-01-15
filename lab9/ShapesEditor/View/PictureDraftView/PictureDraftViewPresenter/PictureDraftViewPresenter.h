#pragma once
#include "../IPictureDraftViewListener.h"
#include "../../../App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../PictureDraftView.h"
#include "../../ShapeView/ShapeViewPresenter/ShapeViewPresenter.h"

class PictureDraftViewPresenter : public IPictureDraftViewListener
{
public:
	PictureDraftViewPresenter(ShapeSelectionModel&, PictureDraftView&, PictureDraftAppModel&);

	void OnMouseDown(const Point&) override;
	void OnDrag(const Point& offset, const Point& point) override;
	void OnMouseUp(const Point&) override;

private:
	ShapeSelectionModel& m_shapeSelectionModel;
	PictureDraftView& m_pictureDraftView;
	PictureDraftAppModel& m_pictureDraftAppModel;
	std::vector<std::shared_ptr<ShapeViewPresenter>> m_shapeViewPresenters;
};
