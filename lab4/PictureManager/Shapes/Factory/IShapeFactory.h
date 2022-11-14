#pragma once
#include <string>
#include <memory>
#include "../Shape.h"

typedef std::unique_ptr<Shape> ShapePtr;

class IShapeFactory
{
public:
	virtual ShapePtr CreateShape(const std::string& description) = 0;

	virtual ~IShapeFactory() = default;
};
