#pragma once
#include "../IView.h"
#include "../../App/ShapeAppModel/ShapeAppModel.h"

class SelectionFrameView : public IView
{
public:
	using Id = std::string;
	SelectionFrameView(ShapeAppModel&);
	Id GetId() const;
	void SetFrame(const RectD&);
	void Show(ICanvas&) override;

private:
	void ShowCorner(ICanvas&, const Point&);

	ShapeAppModel& m_shapeAppModel;
	RectD m_frame;
	Id m_id;
};