#include "../../pch.h"
#include "ShapeSelectionModel.h"

std::vector<std::shared_ptr<ShapeAppModel>> ShapeSelectionModel::GetSelectedShapes() const
{
	return m_selectedShapes;
}

void ShapeSelectionModel::SetSelectedShapes(const std::vector<std::shared_ptr<ShapeAppModel>>& shapes)
{
	m_selectedShapes = shapes;
}

connection ShapeSelectionModel::DoOnSelectionChanged(const std::function<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)>& handler)
{
	return m_selectionChanged.connect(handler);
}
