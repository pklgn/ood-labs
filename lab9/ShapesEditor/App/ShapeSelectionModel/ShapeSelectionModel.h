#pragma once
#include "../History/ICommandsContainer.h"
#include "../ShapeAppModel/ShapeAppModel.h"
#include "../PictureDraftAppModel/PictureDraftAppModel.h"
#include "IShapeSelectionModel.h"

class ShapeSelectionModel : public IShapeSelectionModel
{
public:
	std::vector<std::shared_ptr<ShapeAppModel>> GetSelectedShapes() const;
	void SetSelectedShapes(const std::vector<std::shared_ptr<ShapeAppModel>>&);

	connection DoOnSelectionChanged(const std::function<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)>&);

private:
	std::vector<std::shared_ptr<ShapeAppModel>> m_selectedShapes;
	signal<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)> m_selectionChanged;
};