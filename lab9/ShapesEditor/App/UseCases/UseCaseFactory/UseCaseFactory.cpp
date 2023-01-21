#include "../../../pch.h"
#include "UseCaseFactory.h"

UseCaseFactory::UseCaseFactory(IShapeSelectionModel& selectionModel, ICommandsContainer& commandsContainer)
	: m_shapeSelection(selectionModel)
	, m_commandsContainer(commandsContainer)
{
}

std::unique_ptr<MoveShapeUseCase> UseCaseFactory::CreateMoveShapeUseCase()
{
	return std::make_unique<MoveShapeUseCase>(m_shapeSelection, m_commandsContainer);
}

std::unique_ptr<ResizeShapeUseCase> UseCaseFactory::CreateResizeShapeUseCase()
{
	return std::make_unique<ResizeShapeUseCase>(m_shapeSelection, m_commandsContainer);
}

std::unique_ptr<InsertShapeUseCase> UseCaseFactory::CreateInsertShapeUseCase(PictureDraftAppModel& pictureDraftAppModel)
{
	return std::make_unique<InsertShapeUseCase>(pictureDraftAppModel, m_shapeSelection, m_commandsContainer);
}

std::unique_ptr<DeleteShapeUseCase> UseCaseFactory::CreateDeleteShapeUseCase(PictureDraftAppModel& pictureDraftAppModel)
{
	return std::make_unique<DeleteShapeUseCase>(pictureDraftAppModel, m_shapeSelection, m_commandsContainer);
}
