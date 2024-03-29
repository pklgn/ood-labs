#include "../../pch.h"
#include "ShapeAppModel.h"

ShapeAppModel::ShapeAppModel(std::shared_ptr<Shape> shape)
	: m_shape(shape)
	, m_frame(shape->GetFrame())
{
	m_shape->DoOnFrameChanged([&, this](const RectD& frame) {
		m_frame = frame;
		m_frameChanged(frame);
	});
}

ShapeAppModel::Id ShapeAppModel::GetId() const
{
	return m_shape->GetId();
}

ShapeType ShapeAppModel::GetType() const
{
	return m_shape->GetType();
}

std::shared_ptr<Shape> ShapeAppModel::GetShape() const
{
	return m_shape;
}

RectD ShapeAppModel::GetFrame() const
{
	return m_frame;
}

void ShapeAppModel::SetFrame(const RectD& frame)
{
	m_frame = frame;
	m_frameChanged(m_frame);
}

connection ShapeAppModel::DoOnFrameChanged(const std::function<void(const RectD&)>& handler)
{
	return m_frameChanged.connect(handler);
}
