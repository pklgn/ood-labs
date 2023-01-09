#pragma once
#include "../Shape/IShape.h"

class PictureDraft
{
public:
	size_t GetShapeCount();
	std::shared_ptr<IShape> GetShape(size_t index);
	void InsertShape(std::shared_ptr<IShape> shape, size_t index);
	std::shared_ptr<IShape> DeleteShape(size_t index);
};
