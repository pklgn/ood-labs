#pragma once
#include <memory>
#include "../MoveShapeUseCase/MoveShapeUseCase.h"
#include "../ResizeShapeUseCase/ResizeShapeUseCase.h"
#include "../InsertShapeUseCase/InsertShapeUseCase.h"
#include "../DeleteShapeUseCase/DeleteShapeUseCase.h"

class IUseCaseFactory
{
public:
	virtual ~IUseCaseFactory() = default;

	virtual std::unique_ptr<MoveShapeUseCase> CreateMoveShapeUseCase() = 0;
	virtual std::unique_ptr<ResizeShapeUseCase> CreateResizeShapeUseCase() = 0;
	virtual std::unique_ptr<InsertShapeUseCase> CreateInsertShapeUseCase(PictureDraftAppModel&) = 0;
	virtual std::unique_ptr<DeleteShapeUseCase> CreateDeleteShapeUseCase(PictureDraftAppModel&) = 0;
};
