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

	void SetRespectFrameBorders(size_t width, size_t height);

private:
	bool IsOnCorner(const Point& leftTop, const Point& point);
	void RespectFrameBorders(const std::shared_ptr<ShapeAppModel>&);

	std::shared_ptr<ShapeAppModel> m_shapeAppModel;
	ShapeSelectionModel& m_shapeSelectionModel;
	ShapeView& m_shapeView;
	size_t m_respectFrameWidth = SIZE_MAX;
	size_t m_respectFrameHeight = SIZE_MAX;
};