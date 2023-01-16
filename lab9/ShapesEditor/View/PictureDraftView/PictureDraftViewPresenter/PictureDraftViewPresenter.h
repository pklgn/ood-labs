#pragma once
#include "../../../App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../../ShapeView/ShapeViewPresenter/ShapeViewPresenter.h"
#include "../IPictureDraftViewListener.h"
#include "../PictureDraftView.h"

class PictureDraftViewPresenter : public IPictureDraftViewListener
{
public:
	PictureDraftViewPresenter(ShapeSelectionModel&, PictureDraftView&, PictureDraftAppModel&, IHistory&);

	void OnMouseDown(const Point&) override;
	void OnDrag(const Point& offset, const Point& point) override;
	void OnMouseUp(const Point&) override;

	void InsertShape(ShapeType);
	void DeleteShape();

	void Undo();
	void Redo();

private:
	void SetupShapeView(size_t index);

	ShapeSelectionModel& m_shapeSelectionModel;
	PictureDraftView& m_pictureDraftView;
	PictureDraftAppModel& m_pictureDraftAppModel;
	std::vector<std::shared_ptr<ShapeViewPresenter>> m_shapeViewPresenters;
	IHistory& m_history;
};
