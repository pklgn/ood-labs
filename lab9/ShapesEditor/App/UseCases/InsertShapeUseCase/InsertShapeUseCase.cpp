#include "../../../pch.h"
#include "../../../Model/Shape/Shape.h"
#include "InsertShapeUseCase.h"
#include "../Commands/InsertShapeCommand/InsertShapeCommand.h"
#include "../../PictureDraftAppModel/PictureDraftAppModel.h"


InsertShapeUseCase::InsertShapeUseCase(PictureDraftAppModel& pictureDraft, const std::shared_ptr<IHistory>& history)
	: m_pictureDraft(pictureDraft)
	, m_history(history)
{
}

void InsertShapeUseCase::Insert(size_t index, ShapeType shapeType)
{
	auto shape = std::make_shared<Shape>(shapeType);
	auto domainPictureDraft = m_pictureDraft.GetPictureDraft();
	auto insertCommand = std::make_unique<InsertShapeCommand>(index, shape, domainPictureDraft);
	m_history->AddAndExecuteCommand(std::move(insertCommand));
}