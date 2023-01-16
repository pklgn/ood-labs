#pragma once
#include "../../History/IHistory.h"
#include "../../ShapeAppModel/ShapeAppModel.h"
#include "../../PictureDraftAppModel/PictureDraftAppModel.h"

class DeleteShapeUseCase
{
public:
	DeleteShapeUseCase(const std::vector<std::shared_ptr<ShapeAppModel>>&, PictureDraftAppModel&, const std::shared_ptr<IHistory>&);

	void Delete();

private:
	std::vector<std::shared_ptr<ShapeAppModel>> m_shapesToDelete;
	PictureDraftAppModel& m_pictureDraft;
	std::shared_ptr<IHistory> m_history;
};