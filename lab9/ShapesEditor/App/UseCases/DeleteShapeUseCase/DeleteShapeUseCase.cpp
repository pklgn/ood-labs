#include "../../../pch.h"
#include "../../Command/MacroCommand/MacroCommand.h"
#include "../Commands/DeleteShapeCommand/DeleteShapeCommand.h"
#include "DeleteShapeUseCase.h"

DeleteShapeUseCase::DeleteShapeUseCase(PictureDraftAppModel& pictureDraft, IShapeSelectionModel& selection, ICommandsContainer& commandsContainer)
	: m_selectionModel(selection)
	, m_pictureDraft(pictureDraft)
	, m_commandsContainer(commandsContainer)
{
}

void DeleteShapeUseCase::Delete()
{
	auto deleteShapesMacro = std::make_unique<MacroCommand>();
	auto domainPictureDraft = m_pictureDraft.GetPictureDraft();
	auto shapesToDelete = m_selectionModel.GetSelectedShapes();
	for (auto&& shape : shapesToDelete)
	{
		deleteShapesMacro->AddCommand(std::make_unique<DeleteShapeCommand>(shape->GetShape(), domainPictureDraft, m_selectionModel));
	}
	m_commandsContainer.AddAndExecuteCommand(std::move(deleteShapesMacro));
}
