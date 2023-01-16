#pragma once
#include "../../../common/Point/Point.h"
#include "../../History/IHistory.h"
#include "../../ShapeAppModel/ShapeAppModel.h"
#include "BasePoint/BasePoint.h"

class ResizeShapeUseCase
{
public:
	ResizeShapeUseCase(ShapeSelectionModel& selectionModel, const std::shared_ptr<IHistory>& history);

	void Resize(const Point& offset, BasePoint);
	void Commit();

private:
	void ResizeShape(std::shared_ptr<ShapeAppModel>, const Point& offset, BasePoint);
	ShapeSelectionModel& m_selectionModel;
	std::shared_ptr<IHistory> m_history;
};