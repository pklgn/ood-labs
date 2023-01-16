#pragma once
#include "../../../../common/Frame/Frame.h"
#include "../../../Command/AbstractCommand.h"
#include "../../../ShapeSelectionModel/ShapeSelectionModel.h"

class ChangeFrameCommand : public AbstractCommand
{
public:
	ChangeFrameCommand(const std::shared_ptr<ShapeAppModel>&, ShapeSelectionModel&);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

	void SwapFrame();

private:
	RectD m_frameToApply;
	std::shared_ptr<ShapeAppModel> m_target;
	ShapeSelectionModel& m_selectionModel;
}
;