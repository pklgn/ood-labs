#pragma once
#include "../../../common/Point/Point.h"
#include "../../History/IHistory.h"

class ShapeSelectionModel;

class MoveShapeUseCase
{
public:
	MoveShapeUseCase(ShapeSelectionModel&, const std::shared_ptr<IHistory>&);

	void Move(const Point& offset);
	void Commit();

private:
	ShapeSelectionModel& m_selectionModel;
	std::shared_ptr<IHistory> m_history;
};
