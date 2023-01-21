#pragma once
#include "../../../common/Point/Point.h"
#include "../../History/ICommandsContainer.h"
#include "../../ShapeAppModel/ShapeAppModel.h"
#include "BasePoint/BasePoint.h"

class ResizeShapeUseCase
{
public:
	ResizeShapeUseCase(IShapeSelectionModel&, ICommandsContainer&);

	void Resize(const Point& offset, BasePoint);
	void Commit();

private:
	void ResizeShape(const std::shared_ptr<ShapeAppModel>&, const Point& offset, BasePoint);
	IShapeSelectionModel& m_selectionModel;
	ICommandsContainer& m_commandsContainer;
};