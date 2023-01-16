#pragma once
#include "../../../common/Point/Point.h"
#include "../../History/IHistory.h"
#include "../../ShapeAppModel/ShapeAppModel.h"
#include "BasePoint/BasePoint.h"

class ResizeShapeUseCase
{
public:
	ResizeShapeUseCase(const std::vector<std::shared_ptr<ShapeAppModel>>&, std::shared_ptr<IHistory>);

	void Resize(const Point& offset, BasePoint);
	void Commit();

private:
	void ResizeShape(std::shared_ptr<ShapeAppModel>, const Point& offset, BasePoint);
	std::vector<std::shared_ptr<ShapeAppModel>> m_shapesToResize;
	std::shared_ptr<IHistory> m_history;
};