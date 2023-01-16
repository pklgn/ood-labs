#pragma once
#include "../History/IHistory.h"
#include "../ShapeAppModel/ShapeAppModel.h"
#include "../PictureDraftAppModel/PictureDraftAppModel.h"
#include "../UseCases/DeleteShapeUseCase/DeleteShapeUseCase.h"
#include "../UseCases/MoveShapeUseCase/MoveShapeUseCase.h"
#include "../UseCases/ResizeShapeUseCase/ResizeShapeUseCase.h"

class ShapeSelectionModel
{
public:
	ShapeSelectionModel(const std::shared_ptr<IHistory>&);
	std::vector<std::shared_ptr<ShapeAppModel>> GetSelectedShapes() const;
	void SetSelectedShapes(const std::vector<std::shared_ptr<ShapeAppModel>>&);

	connection DoOnSelectionChanged(const std::function<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)>&);

	// FIXED: сначала реализовать use case'ы
	std::unique_ptr<MoveShapeUseCase> CreateMoveShapeUseCase();
	std::unique_ptr<ResizeShapeUseCase> CreateResizeShapeUseCase();
	std::unique_ptr<DeleteShapeUseCase> CreateDeleteShapeUseCase(PictureDraftAppModel&);

private:
	std::vector<std::shared_ptr<ShapeAppModel>> m_selectedShapes;
	signal<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)> m_selectionChanged;
	std::shared_ptr<IHistory> m_history;
};