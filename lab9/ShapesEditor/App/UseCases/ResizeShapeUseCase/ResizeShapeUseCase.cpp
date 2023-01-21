#include "../../../pch.h"
#include "../../Command/MacroCommand/MacroCommand.h"
#include "../Commands/ChangeFrameCommand/ChangeFrameCommand.h"
#include "ResizeShapeUseCase.h"

const double MIN_WIDTH = 30;
const double MIN_HEIGHT = 30;

ResizeShapeUseCase::ResizeShapeUseCase(IShapeSelectionModel& selectionModel, ICommandsContainer& commandsContainer)
	: m_selectionModel(selectionModel)
	, m_commandsContainer(commandsContainer)
{
}

void ResizeShapeUseCase::Resize(const Point& offset, BasePoint basePoint)
{
	auto shapesToResize = m_selectionModel.GetSelectedShapes();
	for (auto&& shape : shapesToResize)
	{
		ResizeShape(shape, offset, basePoint);
	}
}

void ResizeShapeUseCase::Commit()
{
	auto resizeShapesMacro = std::make_unique<MacroCommand>();
	auto shapesToResize = m_selectionModel.GetSelectedShapes();
	for (auto&& shape : shapesToResize)
	{
		// FIXED: добавить передачу апп фигуры и selection модели
		resizeShapesMacro->AddCommand(std::make_unique<ChangeFrameCommand>(shape, m_selectionModel));
	}
	m_commandsContainer.AddAndExecuteCommand(std::move(resizeShapesMacro));
}

void ResizeShapeUseCase::ResizeShape(const std::shared_ptr<ShapeAppModel>& shape, const Point& offset, BasePoint basePoint)
{
	auto frame = shape->GetFrame();
	double newWidth;
	double newHeight;

	switch (basePoint)
	{
	case BasePoint::LeftTop:
		newWidth = frame.width + offset.x;
		frame.width = std::max(MIN_WIDTH, newWidth);

		newHeight = frame.height + offset.y;
		frame.height = std::max(MIN_HEIGHT, newHeight);

		shape->SetFrame(frame);
		return;
	case BasePoint::RightTop:
		newWidth = frame.width - offset.x;
		frame.width = std::max(MIN_WIDTH, newWidth);

		newHeight = frame.height + offset.y;
		frame.height = std::max(MIN_HEIGHT, newHeight);

		frame.left += offset.x;
		shape->SetFrame(frame);
		return;
	case BasePoint::RightBottom:
		newWidth = frame.width - offset.x;
		frame.width = std::max(MIN_WIDTH, newWidth);

		newHeight = frame.height - offset.y;
		frame.height = std::max(MIN_HEIGHT, newHeight);

		frame.left += offset.x;
		frame.top += offset.y;
		shape->SetFrame(frame);
		return;
	case BasePoint::LeftBottom:
		newWidth = frame.width + offset.x;
		frame.width = std::max(MIN_WIDTH, newWidth);

		newHeight = frame.height - offset.y;
		frame.height = std::max(MIN_HEIGHT, newHeight);

		frame.top += offset.y;
		shape->SetFrame(frame);
		return;
	default:
		throw std::invalid_argument("Unknown base point type was given");
	}
}
