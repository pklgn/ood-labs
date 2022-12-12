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

void SimpleShape::SetFrame(const RectD& frame)
{
	auto currFrame = GetFrame();
	auto currSqrt = hypot(currFrame.width, currFrame.height);
	auto sqrt = hypot(frame.width, frame.height);
	auto sqrtCoef = sqrt / currSqrt;

	auto currThickness = GetLineStyle()->GetThickness();
	GetLineStyle()->SetThickness(currThickness.value_or(0) * sqrtCoef);
}
