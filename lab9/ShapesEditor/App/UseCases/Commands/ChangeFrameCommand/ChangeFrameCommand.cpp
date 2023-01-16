#include "../../../../pch.h"
#include "ChangeFrameCommand.h"
#include "../../../ShapeAppModel/ShapeAppModel.h"

ChangeFrameCommand::ChangeFrameCommand(const std::shared_ptr<ShapeAppModel>& shape, ShapeSelectionModel& selectionModel)
	: m_frameToApply(shape->GetFrame())
	, m_target(shape)
	, m_selectionModel(selectionModel)
{
}

void ChangeFrameCommand::DoExecute()
{
	SwapFrame();
	m_selectionModel.SetSelectedShapes({ m_target });
}

void ChangeFrameCommand::DoUnexecute()
{
	SwapFrame();
	m_selectionModel.SetSelectedShapes({ m_target });
}

void ChangeFrameCommand::SwapFrame()
{
	auto oldFrame = m_target->GetShape()->GetFrame();
	m_target->GetShape()->SetFrame(m_frameToApply);

	m_frameToApply = oldFrame;
}
