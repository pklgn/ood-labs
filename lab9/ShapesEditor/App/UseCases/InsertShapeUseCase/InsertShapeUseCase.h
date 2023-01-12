#pragma once
#include <memory>
#include "../../History/History.h"
#include "../../PictureDraftAppModel/PictureDraftAppModel.h"

class InsertShapeUseCase
{
public:
	InsertShapeUseCase(const PictureDraftAppModel&, const std::shared_ptr<IHistory>&);

	void Insert(ShapeType);

private:
	const PictureDraftAppModel& m_pictureDraft;
	std::shared_ptr<IHistory> m_history;
};