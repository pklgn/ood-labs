#include "../../../pch.h"
#include "../Commands/ChangeFrameCommand/ChangeFrameCommand.h"
#include "MoveShapeUseCase.h"

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
	for (auto&& shape : m_shapesToMove)
	{
		auto domainShape = shape->GetShape();
		auto frame = shape->GetFrame();
		// FIXED: создать команду по перемещению
		m_history->AddAndExecuteCommand(std::make_unique<ChangeFrameCommand>(frame, domainShape));
	}
}
