#pragma once
#include "../IView.h"
#include "../../App/ShapeAppModel/ShapeAppModel.h"

class SelectionFrameView : public IView
{
public:
	SelectionFrameView(ShapeAppModel&);

	void Show(ICanvas&) override;

private:
	ShapeAppModel& m_shapeAppModel;
	RectD m_frame;
};