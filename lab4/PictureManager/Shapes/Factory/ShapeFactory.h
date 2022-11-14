#pragma once
#include <memory>
#include "IShapeFactory.h"

class ShapeFactory : public IShapeFactory
{
public:
	ShapePtr CreateShape(const std::string& description) override;
};
