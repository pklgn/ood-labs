#pragma once
#include <memory>
#include "../Shape/Shape.h"

class IPictureDraft
{
public:
	virtual ~IPictureDraft() = default;

	virtual size_t GetShapeCount() const = 0;
	virtual std::shared_ptr<Shape> GetShape(size_t index) const = 0;
	virtual void InsertShape(const std::shared_ptr<Shape>& shape, size_t index) = 0;
	virtual std::shared_ptr<Shape> DeleteShape(size_t index) = 0;
};