#pragma once
#include "../IShape.h"
#include "../../Style/LineStyle/SimpleLineStyle/SimpleLineStyle.h"
#include "../../Style/FillStyle/SimpleFillStyle/SimpleFillStyle.h"

class SimpleShape : public IShape
	, public std::enable_shared_from_this<SimpleShape>
{
public:
	SimpleShape(const RectD&, const std::shared_ptr<SimpleLineStyle>, const std::shared_ptr<SimpleFillStyle>);

	RectD GetFrame() override;
	void SetFrame(const RectD&) override;

	std::shared_ptr<ILineStyle> GetLineStyle() override;
	std::shared_ptr<const ILineStyle> GetLineStyle() const override;
	void SetLineStyle(std::shared_ptr<ILineStyle>) override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	std::shared_ptr<const IFillStyle> GetFillStyle() const override;
	void SetFillStyle(std::shared_ptr<IFillStyle>) override;

	std::shared_ptr<const IShape> GetGroupShape() const override;

private:
	//TODO: выпилить frame и перенести в concretesimpleshape: например triangle
	RectD m_frame;
	std::shared_ptr<SimpleLineStyle> m_lineStyle;
	std::shared_ptr<SimpleFillStyle> m_fillStyle;
};
