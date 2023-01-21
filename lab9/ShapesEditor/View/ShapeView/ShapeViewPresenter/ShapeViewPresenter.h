#pragma once
#include "../../../App/ShapeAppModel/ShapeAppModel.h"
#include "../../../App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../../../App/UseCases/UseCaseFactory/IUseCaseFactory.h"
#include "../IShapeViewListener.h"
#include "../ShapeView.h"

class ShapeViewPresenter : public IShapeViewListener
{
public:
	ShapeViewPresenter(const std::shared_ptr<ShapeAppModel>& model, IUseCaseFactory&, ShapeSelectionModel& selectionModel, const std::shared_ptr<ShapeView>& shapeView);

	std::shared_ptr<ShapeView> GetShapeView() const;

	void OnMouseDown(const Point&) override;
	void OnDrag(const Point& offset, const Point& point) override;
	void OnMouseUp(const Point&) override;

	void SetRespectFrameBorders(size_t width, size_t height);

private:
	bool IsOnCorner(const Point& leftTop, const Point& point);
	void RespectFrameBorders(const std::shared_ptr<ShapeAppModel>&);

	std::shared_ptr<ShapeAppModel> m_shapeAppModel;
	IUseCaseFactory& m_useCaseFactory;
	ShapeSelectionModel& m_shapeSelectionModel;
	std::shared_ptr<ShapeView> m_shapeView;
	size_t m_respectFrameWidth = SIZE_MAX;
	size_t m_respectFrameHeight = SIZE_MAX;
};