#pragma once
#include "IUseCaseFactory.h"

class UseCaseFactory : public IUseCaseFactory
{
public:
	UseCaseFactory(IShapeSelectionModel&, ICommandsContainer&);

	std::unique_ptr<MoveShapeUseCase> CreateMoveShapeUseCase() override;
	std::unique_ptr<ResizeShapeUseCase> CreateResizeShapeUseCase() override;
	std::unique_ptr<InsertShapeUseCase> CreateInsertShapeUseCase(PictureDraftAppModel&) override;
	std::unique_ptr<DeleteShapeUseCase> CreateDeleteShapeUseCase(PictureDraftAppModel&) override;

private:
	IShapeSelectionModel& m_shapeSelection;
	ICommandsContainer& m_commandsContainer;
};