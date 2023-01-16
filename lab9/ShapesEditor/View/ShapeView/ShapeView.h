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
	using Id = std::string;
	ShapeView(const Id&, const RectD&, ShapeType, uint32_t lineColor = 0x2F528FFF, uint32_t fillColor = 0x4472C4FF);
	Id GetId() const;
	void SetFrame(const RectD&);
	RectD GetFrame() const;
	uint32_t GetLineColor() const;
	uint32_t GetFillColor() const;
	ShapeType GetShapeType() const;
	
	void Show(ICanvas&) override;

private:
	void ShowRectangle(ICanvas&);
	void ShowTriangle(ICanvas&);
	void ShowEllipse(ICanvas&);

	Id m_id;
	RectD m_frame;
	ShapeType m_type;
	uint32_t m_lineColor;
	uint32_t m_fillColor;
};