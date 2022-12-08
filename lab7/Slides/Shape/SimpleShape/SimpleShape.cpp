#include "../../pch.h"
#include "SimpleShape.h"

SimpleShape::SimpleShape(const std::shared_ptr<ILineStyle> lineStyle, const std::shared_ptr<IFillStyle> fillStyle)
	: m_lineStyle(lineStyle)
	, m_fillStyle(fillStyle)
{
}

std::shared_ptr<ILineStyle> SimpleShape::GetLineStyle()
{
	return m_lineStyle;
}

std::shared_ptr<const ILineStyle> SimpleShape::GetLineStyle() const
{
	return m_lineStyle;
}

std::shared_ptr<IFillStyle> SimpleShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IFillStyle> SimpleShape::GetFillStyle() const
{
	return m_fillStyle;
}


std::shared_ptr<const IShape> SimpleShape::GetGroupShape() const
{
	return nullptr;
}
