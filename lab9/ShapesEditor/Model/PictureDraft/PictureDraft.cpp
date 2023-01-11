#include "../../pch.h"
#include "PictureDraft.h"

size_t PictureDraft::GetShapeCount()
{
	return m_shapes.size();
}

std::shared_ptr<Shape> PictureDraft::GetShape(size_t index)
{
	return m_shapes.at(index);
}

void PictureDraft::InsertShape(std::shared_ptr<Shape> shape, size_t index)
{
	auto size = m_shapes.size();
	if (size < index)
	{
		throw std::out_of_range("Specified index for insertion is out of range");
	}
	if (size == index)
	{
		m_shapes.push_back(shape);
		return;
	}
	m_shapes.insert(m_shapes.begin() + index, shape);
}

std::shared_ptr<Shape> PictureDraft::DeleteShape(size_t index)
{
	auto shapeToDelete = m_shapes.at(index);
	m_shapes.erase(m_shapes.begin() + index);
	return shapeToDelete;
}

connection PictureDraft::DoOnShapeAdded(const std::function<void(size_t index)>& handler)
{
	return m_shapeAdded.connect(handler);
}

connection PictureDraft::DoOnShapeDeleted(const std::function<void(size_t index, std::shared_ptr<Shape> shape)>& handler)
{
	return m_shapeDeleted.connect(handler);
}
