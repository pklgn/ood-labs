#pragma once
#include "../../History/ICommandsContainer.h"
#include "../../ShapeSelectionModel/IShapeSelectionModel.h"
#include "../../History/ICommandsContainer.h"
#include "../../PictureDraftAppModel/PictureDraftAppModel.h"

class InsertShapeUseCase
{
public:
	InsertShapeUseCase(PictureDraftAppModel&, IShapeSelectionModel&, ICommandsContainer&);

	void Insert(size_t index, ShapeType);

private:
	PictureDraftAppModel& m_pictureDraftAppModel;
	IShapeSelectionModel& m_selectionModel;
	ICommandsContainer& m_commandsContainer;
};
