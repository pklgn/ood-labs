#include "../../../pch.h"
#include "../../../Model/Shape/Shape.h"
#include "InsertShapeUseCase.h"
#include "../Commands/InsertShapeCommand/InsertShapeCommand.h"
#include "../../PictureDraftAppModel/PictureDraftAppModel.h"


InsertShapeUseCase::InsertShapeUseCase(PictureDraftAppModel& pictureDraft, IShapeSelectionModel& selection, ICommandsContainer& commandsContainer)
	: m_pictureDraftAppModel(pictureDraft)
	, m_commandsContainer(commandsContainer)
	, m_selectionModel(selection)
{
}

void InsertShapeUseCase::Insert(size_t index, ShapeType shapeType)
{
	auto shape = std::make_shared<Shape>(shapeType);
	auto domainPictureDraft = m_pictureDraftAppModel.GetPictureDraft();
	auto insertCommand = std::make_unique<InsertShapeCommand>(index, shape, domainPictureDraft, m_selectionModel);
	m_commandsContainer.AddAndExecuteCommand(std::move(insertCommand));
}