#pragma once
#include <memory>
#include <vector>
#include "../Shape/IShape.h"

class Slide : public IDrawable
{
public:
	size_t GetShapesCount() const;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index);
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t index);
	void RemoveShapeAtIndex(size_t index);

	void Draw(ICanvas& canvas) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
