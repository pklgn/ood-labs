#include "../../../pch.h"
#include "../../Command/MacroCommand/MacroCommand.h"
#include "../Commands/ChangeFrameCommand/ChangeFrameCommand.h"
#include "MoveShapeUseCase.h"

MoveShapeUseCase::MoveShapeUseCase(const std::vector<std::shared_ptr<ShapeAppModel>>& shapes, std::shared_ptr<IHistory> history)
	: m_shapesToMove(shapes)
	, m_history(history)
{
}

void MoveShapeUseCase::Move(const Point& offset)
{
	for (auto&& shape : m_shapesToMove)
	{
		auto frame = shape->GetFrame();
		frame.left += offset.x;
		frame.top += offset.y;
		shape->SetFrame(frame);
	}
}

void MoveShapeUseCase::Commit()
{
	auto moveShapesMacro = std::make_unique<MacroCommand>();
	for (auto&& shape : m_shapesToMove)
	{
		auto domainShape = shape->GetShape();
		auto frame = shape->GetFrame();
		// FIXED: создать команду по перемещению
		moveShapesMacro->AddCommand(std::make_unique<ChangeFrameCommand>(frame, domainShape));
	}
	m_history->AddAndExecuteCommand(std::move(moveShapesMacro));
}
