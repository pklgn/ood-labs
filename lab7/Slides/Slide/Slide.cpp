#include "../pch.h"
#include "Slide.h"

size_t Slide::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> Slide::GetShapeAtIndex(size_t index)
{
	return m_shapes.at(index);
}

void Slide::InsertShape(const std::shared_ptr<IShape>& shape, size_t index)
{
	if (m_shapes.size() < index)
	{
		throw std::out_of_range("Index value is out of range");
	}

	m_shapes.insert(m_shapes.begin() + index, shape);
}

void Slide::RemoveShapeAtIndex(size_t index)
{
	if (m_shapes.size() <= index)
	{
		throw std::out_of_range("Index value is out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

void Slide::Draw(ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}
