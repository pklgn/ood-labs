#pragma once
#include "../../../Command/AbstractCommand.h"
#include "../../../../common/Frame/Frame.h"
#include "../../../../model/Shape/Shape.h"

class ChangeFrameCommand : public AbstractCommand
{
public:
	ChangeFrameCommand(const RectD& frame, std::shared_ptr<Shape>);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

	void SwapFrame();

private:
	RectD m_frameToApply;
	std::shared_ptr<Shape> m_target;
}
;