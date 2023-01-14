#pragma once
#include <memory>
#include <boost/signals2.hpp>
#include "../../Model/Shape/Shape.h"

using namespace boost::signals2;

class ShapeAppModel
{
public:
	using Id = std::string;
	ShapeAppModel(std::shared_ptr<Shape>);
	Id GetId() const;
	std::shared_ptr<Shape> GetShape() const;
	RectD GetFrame() const;
	void SetFrame(const RectD& frame);
	std::shared_ptr<ILineStyle> GetLineStyle() const;
	std::shared_ptr<IFillStyle> GetFillStyle() const;
	
	connection DoOnFrameChanged(const std::function<void(const RectD&)>&);

private:
	Id m_id;
	RectD m_frame;
	std::shared_ptr<Shape> m_shape;
	signal<void(const RectD&)> m_frameChanged;
};