#include "../../pch.h"
#include "SimpleShape.h"

SimpleShape::SimpleShape(const RectD& frame, const std::shared_ptr<SimpleLineStyle> lineStyle, const std::shared_ptr<SimpleFillStyle> fillStyle)
	: m_frame(frame)
	, m_lineStyle(lineStyle)
	, m_fillStyle(fillStyle)
{
}

RectD SimpleShape::GetFrame()
{
	return m_frame;
}

void SimpleShape::SetFrame(const RectD& frame)
{
	m_frame = frame;
}

std::shared_ptr<ILineStyle> SimpleShape::GetLineStyle()
{
	return m_lineStyle;
}

std::shared_ptr<const ILineStyle> SimpleShape::GetLineStyle() const
{
	return m_lineStyle;
}

void SimpleShape::SetLineStyle(std::shared_ptr<ILineStyle> lineStyle)
{
	auto simpleLineStyle = std::dynamic_pointer_cast<SimpleLineStyle>(lineStyle);
	if (!simpleLineStyle)
	{
		throw std::invalid_argument("Couldn't apply specified line style");
	}

	m_lineStyle = simpleLineStyle;
}

std::shared_ptr<IFillStyle> SimpleShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IFillStyle> SimpleShape::GetFillStyle() const
{
	return m_fillStyle;
}

void SimpleShape::SetFillStyle(std::shared_ptr<IFillStyle> fillStyle)
{
	auto simpleFillStyle = std::dynamic_pointer_cast<SimpleFillStyle>(fillStyle);
	if (!simpleFillStyle)
	{
		throw std::invalid_argument("Couldn't apply specified line style");
	}

	m_fillStyle = simpleFillStyle;
}

std::shared_ptr<const IShape> SimpleShape::GetGroupShape() const
{
	return nullptr;
}
