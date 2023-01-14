#pragma once
#include "../../App/ShapeAppModel/ShapeAppModel.h"
#include "../../common/Frame/Frame.h"
#include "../../Model/Style/FillStyle/IFillStyle.h"
#include "../../Model/Style/LineStyle/ILineStyle.h"
#include "../IView.h"
#include "IShapeViewListener.h"

class ShapeView : public IView
{
public:
	ShapeView(const RectD&, ShapeType, uint32_t lineColor, uint32_t fillColor);

	void SetFrame(const RectD&);
	RectD GetFrame() const;
	uint32_t GetLineColor() const;
	uint32_t GetFillColor() const;
	ShapeType GetShapeType() const;
	void SetListener(std::shared_ptr<IShapeViewListener>);
	
	void Show(ICanvas&) override;

private:
	void ShowRectangle(ICanvas&);
	void ShowTriangle(ICanvas&);
	void ShowEllipse(ICanvas&);

	RectD m_frame;
	ShapeType m_type;
	uint32_t m_lineColor;
	uint32_t m_fillColor;
	std::shared_ptr<IShapeViewListener> m_listener;
};