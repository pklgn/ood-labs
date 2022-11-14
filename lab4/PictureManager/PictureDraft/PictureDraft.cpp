#include "../pch.h"
#include "PictureDraft.h"

size_t PictureDraft::GetShapeCount() const
{
	return m_storage.size();
}

Storage::const_iterator PictureDraft::GetShape(size_t index) const
{
	if (m_storage.size() <=  index)
	{
		return m_storage.end();
	}

	return m_storage.begin() + index;
}

void PictureDraft::AddShape(ShapePtr&& shape)
{
	if (shape != nullptr)
	{
		m_storage.push_back(std::move(shape));
	}
}

Storage::const_iterator PictureDraft::begin() const
{
	return m_storage.begin();
}

Storage::const_iterator PictureDraft::end() const
{
	return m_storage.end();
}
