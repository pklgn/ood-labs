#include "../../../pch.h"
#include "../../Command/MacroCommand/MacroCommand.h"
#include "../Commands/ChangeFrameCommand/ChangeFrameCommand.h"
#include "MoveShapeUseCase.h"

MoveShapeUseCase::MoveShapeUseCase(IShapeSelectionModel& selectionModel, ICommandsContainer& commandsContainer)
	: m_selectionModel(selectionModel)
	, m_commandsContainer(commandsContainer)
{
}

void MoveShapeUseCase::Move(const Point& offset)
{
	auto shapesToMove = m_selectionModel.GetSelectedShapes();
	for (auto&& shape : shapesToMove)
	{
		auto frame = shape->GetFrame();
		frame.left += offset.x;
		frame.top += offset.y;
		if (offset.x != 0 || offset.y != 0)
		{
			shape->SetFrame(frame);
		}
	}
}

void MoveShapeUseCase::Commit()
{
	auto moveShapesMacro = std::make_unique<MacroCommand>();
	auto shapesToMove = m_selectionModel.GetSelectedShapes();
	for (auto&& shape : shapesToMove)
	{
		// FIXED: создать команду по перемещению
		moveShapesMacro->AddCommand(std::make_unique<ChangeFrameCommand>(shape, m_selectionModel));
	}
	m_commandsContainer.AddAndExecuteCommand(std::move(moveShapesMacro));
}
