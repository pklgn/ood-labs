#pragma once
#include "../../../common/Point/Point.h"
#include "../../History/IHistory.h"
#include "../../ShapeAppModel/ShapeAppModel.h"

class MoveShapeUseCase
{
public:
	MoveShapeUseCase(const std::vector<std::shared_ptr<ShapeAppModel>>&, std::shared_ptr<IHistory>);

	void Move(const Point& offset);
	void Commit();

private:
	std::vector<std::shared_ptr<ShapeAppModel>> m_shapesToMove;
	std::shared_ptr<IHistory> m_history;
};
