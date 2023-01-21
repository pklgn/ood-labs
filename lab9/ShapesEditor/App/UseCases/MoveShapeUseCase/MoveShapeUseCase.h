#pragma once
#include "../../../common/Point/Point.h"
#include "../../History/ICommandsContainer.h"
#include "../../ShapeSelectionModel/IShapeSelectionModel.h"

class MoveShapeUseCase
{
public:
	MoveShapeUseCase(IShapeSelectionModel&, ICommandsContainer&);

	void Move(const Point& offset);
	void Commit();

private:
	IShapeSelectionModel& m_selectionModel;
	ICommandsContainer& m_commandsContainer;
};
