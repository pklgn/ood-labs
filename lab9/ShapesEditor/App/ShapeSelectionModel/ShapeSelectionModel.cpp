#include "../../pch.h"
#include "ShapeSelectionModel.h"
#include "../UseCases/MoveShapeUseCase/MoveShapeUseCase.h"

ShapeSelectionModel::ShapeSelectionModel(ICommandsContainer& commandsContainer)
	: m_commandsContainer(commandsContainer)
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
