#pragma once
#include "../ShapeAppModel/ShapeAppModel.h"

class ShapeSelectionModel
{
public:
	std::vector<std::shared_ptr<ShapeAppModel>> GetSelectedShapes() const;
	void SetSelectedShapes(const std::vector<std::shared_ptr<ShapeAppModel>>&);

	connection DoOnSelectionChanged(const std::function<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)>&);

	// TODO: сначала реализовать use case'ы
	void CreateMoveShapeUseCase();
	void CreateResizeShapeUseCase();
	void CreateDeleteShapeUseCase();

private:
	std::vector<std::shared_ptr<ShapeAppModel>> m_selectedShapes;
	signal<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)> m_selectionChanged;
	//std::shared_ptr<IHistory> m_history;
};