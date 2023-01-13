#pragma once
#include <memory>
#include "../../History/IHistory.h"

class PictureDraftAppModel;

class InsertShapeUseCase
{
public:
	InsertShapeUseCase(PictureDraftAppModel&, const std::shared_ptr<IHistory>&);

	void Insert(size_t index, ShapeType);

private:
	PictureDraftAppModel& m_pictureDraft;
	std::shared_ptr<IHistory> m_history;
};
