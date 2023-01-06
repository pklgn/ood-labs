#pragma once
#include "ISlide.h"

class Slide : public ISlide
{
public:
	size_t GetShapesCount() const override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	void Draw(ICanvas& canvas) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
