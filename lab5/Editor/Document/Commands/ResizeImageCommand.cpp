#include "../../pch.h"
#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(std::shared_ptr<IImage>& image, size_t newWidth, size_t newHeight)
	: m_target(image)
	, m_resizeWidth(newWidth)
	, m_resizeHeight(newHeight)
{
}

void ResizeImageCommand::DoExecute()
{
	SwapSize();
}

void ResizeImageCommand::DoUnexecute()
{
	SwapSize();
}

void ResizeImageCommand::SwapSize()
{
	auto oldWidth = m_target->GetWidth();
	auto oldHeight = m_target->GetHeight();
	m_target->Resize(m_resizeWidth, m_resizeHeight);

	m_resizeWidth = oldWidth;
	m_resizeHeight = oldHeight;
}
