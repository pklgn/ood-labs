#pragma once
#include "../Canvas/ICanvas.h"

class Shape
{
public:
	Shape(const Color&);

	virtual void Draw(ICanvas&) const = 0;
	Color GetColor() const;

	virtual ~Shape() = default;

private:
	Color m_color;
};