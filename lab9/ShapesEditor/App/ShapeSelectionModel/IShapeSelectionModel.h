#pragma once
#include <vector>
#include <memory>
#include "../ShapeAppModel/ShapeAppModel.h"

class IShapeSelectionModel
{
public:
	virtual ~IShapeSelectionModel() = default;

	virtual std::vector<std::shared_ptr<ShapeAppModel>> GetSelectedShapes() const = 0;
	virtual void SetSelectedShapes(const std::vector<std::shared_ptr<ShapeAppModel>>&) = 0;
};