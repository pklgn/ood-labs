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
	ShapeType GetType() const;
	std::shared_ptr<Shape> GetShape() const;
	RectD GetFrame() const;
	void SetFrame(const RectD& frame);
	
	connection DoOnFrameChanged(const std::function<void(const RectD&)>&);

private:
	RectD m_frame;
	std::shared_ptr<Shape> m_shape;
	signal<void(const RectD&)> m_frameChanged;
};