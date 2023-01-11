#include "../../../pch.h"
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
	for (auto&& shape : m_shapesToMove)
	{
		auto domainShape = shape->GetShape();
		auto frame = shape->GetFrame();
		// FIXED: создать команду по перемещению
		m_history->AddAndExecuteCommand(std::make_unique<ChangeFrameCommand>(frame, domainShape));
	}
}
