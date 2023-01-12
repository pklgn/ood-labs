#include "../../../pch.h"
#include "InsertShapeUseCase.h"

InsertShapeUseCase::InsertShapeUseCase(const PictureDraftAppModel& pictureDraft, const std::shared_ptr<IHistory>& history)
	: m_pictureDraft(pictureDraft)
	, m_history(history)
{
}

void InsertShapeUseCase::Insert(ShapeType shapeType)
{
	switch (shapeType)
	{
	case ShapeType::Rectangle:
		break;
	case ShapeType::Triangle:
		break;
	case ShapeType::Ellipse:
		break;
	default:
		break;
	}
}