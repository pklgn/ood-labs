#include "../../pch.h"
#include "ShapeSelectionModel.h"
#include "../UseCases/MoveShapeUseCase/MoveShapeUseCase.h"

ShapeSelectionModel::ShapeSelectionModel(const std::shared_ptr<IHistory>& history)
	: m_history(history)
{
}

std::vector<std::shared_ptr<ShapeAppModel>> ShapeSelectionModel::GetSelectedShapes() const
{
	return m_selectedShapes;
}

void ShapeSelectionModel::SetSelectedShapes(const std::vector<std::shared_ptr<ShapeAppModel>>& shapes)
{
	m_selectedShapes = shapes;
	m_selectionChanged(shapes);
}

connection ShapeSelectionModel::DoOnSelectionChanged(const std::function<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)>& handler)
{
	return m_selectionChanged.connect(handler);
}

std::unique_ptr<MoveShapeUseCase> ShapeSelectionModel::CreateMoveShapeUseCase()
{
	return std::make_unique<MoveShapeUseCase>(*this, m_history);
}

std::unique_ptr<ResizeShapeUseCase> ShapeSelectionModel::CreateResizeShapeUseCase()
{
	return std::make_unique<ResizeShapeUseCase>(*this, m_history);
}

std::unique_ptr<DeleteShapeUseCase> ShapeSelectionModel::CreateDeleteShapeUseCase(PictureDraftAppModel& pictureDraft)
{
	return std::make_unique<DeleteShapeUseCase>(m_selectedShapes, pictureDraft, m_history);
}
