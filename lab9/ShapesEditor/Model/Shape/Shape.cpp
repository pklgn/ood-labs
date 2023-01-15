#include "../../pch.h"
#include "Shape.h"
#include "../Style/LineStyle/LineStyle.h"
#include "../Style/FillStyle/FillStyle.h"


Shape::Shape(ShapeType type, const RectD& frame)
	: m_lineStyle(std::make_shared<LineStyle>())
	, m_fillStyle(std::make_shared<FillStyle>())
	, m_frame(frame)
	, m_type(type)
{
	auto id = boost::uuids::random_generator_mt19937()();
	m_id = boost::uuids::to_string(id);
}

Shape::Id Shape::GetId() const
{
	return m_id;
}

ShapeType Shape::GetType() const
{
	return m_type;
}

RectD Shape::GetFrame() const
{
	return m_frame;
}

void Shape::SetFrame(const RectD& frame)
{
	m_frame = frame;
}

std::shared_ptr<ILineStyle> Shape::GetLineStyle()
{
	return m_lineStyle;
}

std::shared_ptr<const ILineStyle> Shape::GetLineStyle() const
{
	return m_lineStyle;
}

std::shared_ptr<IFillStyle> Shape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IFillStyle> Shape::GetFillStyle() const
{
	return m_fillStyle;
}

connection Shape::DoOnFrameChanged(const std::function<void(const RectD&)>& handler)
{
	return m_frameChanged.connect(handler);
}
