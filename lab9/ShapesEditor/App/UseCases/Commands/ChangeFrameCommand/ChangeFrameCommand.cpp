#include "../../../../pch.h"
#include "ChangeFrameCommand.h"

ChangeFrameCommand::ChangeFrameCommand(const RectD& newFrame, std::shared_ptr<Shape> shape)
	: m_frameToApply(newFrame)
	, m_target(shape)
{
}

void ChangeFrameCommand::DoExecute()
{
	SwapFrame();
}

void ChangeFrameCommand::DoUnexecute()
{
	SwapFrame();
}

void ChangeFrameCommand::SwapFrame()
{
	auto oldFrame = m_target->GetFrame();
	m_target->SetFrame(m_frameToApply);

	m_frameToApply = oldFrame;
}
