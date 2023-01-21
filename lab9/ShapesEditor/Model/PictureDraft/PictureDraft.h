#pragma once
#include <boost/signals2.hpp>
#include <vector>
#include "../Shape/Shape.h"
#include "IPictureDraft.h"

using namespace boost::signals2;

class PictureDraft : public IPictureDraft
{
public:
	size_t GetShapeCount() const override;
	std::shared_ptr<Shape> GetShape(size_t index) const override;
	void InsertShape(const std::shared_ptr<Shape>& shape, size_t index) override;
	std::shared_ptr<Shape> DeleteShape(size_t index) override;

	connection DoOnShapeAdded(const std::function<void(size_t index)>&);
	connection DoOnShapeDeleted(const std::function<void(size_t index, const std::shared_ptr<IShape>&)>&);

private:
	std::vector<std::shared_ptr<Shape>> m_shapes;
	signal<void(size_t index)> m_shapeAdded;
	signal<void(size_t index, const std::shared_ptr<Shape>&)> m_shapeDeleted;
};
