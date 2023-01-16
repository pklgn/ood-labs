#pragma once
#include "../IView.h"
#include "../../App/ShapeAppModel/ShapeAppModel.h"

class SelectionFrameView : public IView
{
public:
	using Id = std::string;
	SelectionFrameView(ShapeAppModel&);
	void Show(ICanvas&) override;

private:
	void ShowCorner(ICanvas&, const Point&);

	ShapeAppModel& m_shapeAppModel;
};