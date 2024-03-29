#pragma once
#include "../../../../common/Frame/Frame.h"
#include "../../../Command/AbstractCommand.h"
#include "../../../ShapeSelectionModel/IShapeSelectionModel.h"

class ChangeFrameCommand : public AbstractCommand
{
public:
	ChangeFrameCommand(const std::shared_ptr<ShapeAppModel>&, IShapeSelectionModel&);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

	void SwapFrame();

private:
	RectD m_frameToApply;
	std::shared_ptr<ShapeAppModel> m_target;
	IShapeSelectionModel& m_selectionModel;
}
;