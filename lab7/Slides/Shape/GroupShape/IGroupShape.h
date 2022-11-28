#pragma once
#include "../IShape.h"

class IGroupShape : public IShape
{
public:
	virtual size_t GetShapesCount() = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t) = 0;
	virtual void InsertShape(std::shared_ptr<IShape>, size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t) = 0;
};