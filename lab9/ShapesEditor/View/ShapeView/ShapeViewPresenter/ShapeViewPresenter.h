#pragma once
#include "../IShapeViewListener.h"
#include "../../../App/ShapeAppModel/ShapeAppModel.h"
#include "../../../App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../ShapeView.h"

class ShapeViewPresenter : public IShapeViewListener
{
public:
	void OnMouseDown(const Point&) override;
	void OnDrag(const Point&) override;
	void OnMouseUp(const Point&) override;

private:
	std::shared_ptr<ShapeAppModel> m_shapeAppModel;
	ShapeSelectionModel& m_shapeSelectionModel;
	ShapeView& m_shapeView;
};