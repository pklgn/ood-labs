#pragma once
#include <boost/signals2.hpp>
#include <vector>
#include "../Shape/Shape.h"

using namespace boost::signals2;

class PictureDraft
{
public:
	size_t GetShapeCount();
	std::shared_ptr<Shape> GetShape(size_t index);
	void InsertShape(std::shared_ptr<Shape> shape, size_t index);
	std::shared_ptr<Shape> DeleteShape(size_t index);

	connection DoOnShapeAdded(const std::function<void(size_t index)>&);
	connection DoOnShapeDeleted(const std::function<void(size_t index)>&);

private:
	std::vector<std::shared_ptr<Shape>> m_shapes;
	signal<void(size_t index)> m_shapeAdded;
	signal<void(size_t index)> m_shapeDeleted;
};
