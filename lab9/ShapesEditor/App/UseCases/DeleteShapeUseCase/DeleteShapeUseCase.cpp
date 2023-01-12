#include "../../../pch.h"
#include "../../Command/MacroCommand/MacroCommand.h"
#include "../Commands/DeleteShapeCommand/DeleteShapeCommand.h"
#include "DeleteShapeUseCase.h"

DeleteShapeUseCase::DeleteShapeUseCase(const std::vector<std::shared_ptr<ShapeAppModel>>& shapes, const std::shared_ptr<PictureDraftAppModel>& pictureDraft, const std::shared_ptr<IHistory>& history)
	: m_shapesToDelete(shapes)
	, m_pictureDraft(pictureDraft)
	, m_history(history)
{
}

void DeleteShapeUseCase::Delete()
{
	auto deleteShapesMacro = std::make_unique<MacroCommand>();
	auto domainPictureDraft = m_pictureDraft->GetPictureDraft();
	for (auto&& shape : m_shapesToDelete)
	{
		deleteShapesMacro->AddCommand(std::make_unique<DeleteShapeCommand>(shape->GetShape(), domainPictureDraft));
	}
	m_history->AddAndExecuteCommand(std::move(deleteShapesMacro));
}
