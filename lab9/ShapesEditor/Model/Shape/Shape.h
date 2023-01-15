#pragma once
#include <functional>
#include <boost/signals2.hpp>
#include "IShape.h"

using namespace boost::signals2;

class Shape : public IShape
{
public:
	// TODO: разобраться, как вынести значение в cpp файл и нужно ли это?
	inline static const RectD DEFAULT_FRAME = { 0, 0, 100, 100 };

	Shape(ShapeType type, const RectD& frame = DEFAULT_FRAME);
	Id GetId() const override;
	ShapeType GetType() const;

	RectD GetFrame() const override;
	void SetFrame(const RectD&) override;

	std::shared_ptr<ILineStyle> GetLineStyle() override;
	std::shared_ptr<const ILineStyle> GetLineStyle() const override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	std::shared_ptr<const IFillStyle> GetFillStyle() const override;

	connection DoOnFrameChanged(const std::function<void(const RectD&)>&);

private:
	ShapeType m_type;
	Id m_id;
	std::shared_ptr<ILineStyle> m_lineStyle;
	std::shared_ptr<IFillStyle> m_fillStyle;
	RectD m_frame;
	signal<void(const RectD&)> m_frameChanged;
};
