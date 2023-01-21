#pragma once
#include "../../History/ICommandsContainer.h"
#include "../../PictureDraftAppModel/PictureDraftAppModel.h"
#include "../../ShapeSelectionModel/IShapeSelectionModel.h"

class DeleteShapeUseCase
{
public:
	DeleteShapeUseCase(PictureDraftAppModel&, IShapeSelectionModel&, ICommandsContainer&);

	void Delete();

private:
	IShapeSelectionModel& m_selectionModel;
	PictureDraftAppModel& m_pictureDraft;
	ICommandsContainer& m_commandsContainer;
};