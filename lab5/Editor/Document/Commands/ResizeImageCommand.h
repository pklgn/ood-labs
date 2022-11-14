#pragma once
#include "../../Command/AbstractCommand.h"
#include "../../Document/HTMLDocument.h"

class ResizeImageCommand : public AbstractCommand
{
public:
	ResizeImageCommand(std::shared_ptr<IImage>& image, size_t newWidth, size_t newHeight);

protected:
	void DoExecute() override;

	void DoUnexecute() override;

	void SwapSize();

private:
	std::shared_ptr<IImage> m_target;
	size_t m_resizeWidth;
	size_t m_resizeHeight;
};