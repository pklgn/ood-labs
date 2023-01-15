#pragma once
#include "../IShapeViewListener.h"
#include "../../../App/ShapeAppModel/ShapeAppModel.h"
#include "../../../App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../ShapeView.h"

class ShapeViewPresenter : public IShapeViewListener
{
public:
	ShapeViewPresenter(const std::shared_ptr<ShapeAppModel>& model, ShapeSelectionModel& selectionModel, ShapeView& shapeView);

	const ShapeView& GetShapeView() const;

	void OnMouseDown(const Point&) override;
	void OnDrag(const Point& offset, const Point& point) override;
	void OnMouseUp(const Point&) override;

private:
	bool IsOnCorner(const Point& leftTop, const Point& point);

	std::shared_ptr<ShapeAppModel> m_shapeAppModel;
	ShapeSelectionModel& m_shapeSelectionModel;
	ShapeView& m_shapeView;
};