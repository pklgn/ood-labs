#include "../../pch.h"
#include "GroupShape.h"
#include "../../Style/LineStyle/Enumerator/LineStyleEnumerator.hpp"
#include "../../Style/FillStyle/Enumerator/FillStyleEnumerator.hpp"

typedef std::vector<std::shared_ptr<IShape>> Shapes;

GroupShape::GroupShape()
	: m_lineStyle(std::make_shared<CompositeLineStyle>(std::make_unique<LineStyleEnumerator<Shapes>>(m_shapes)))
	, m_fillStyle(std::make_shared<CompositeFillStyle>(std::make_unique<FillStyleEnumerator<Shapes>>(m_shapes)))
{
}

GroupShape::GroupShape(Shapes& shapes)
	: m_shapes(shapes)
	, m_lineStyle(std::make_shared<CompositeLineStyle>(std::make_unique<LineStyleEnumerator<Shapes>>(m_shapes)))
	, m_fillStyle(std::make_shared<CompositeFillStyle>(std::make_unique<FillStyleEnumerator<Shapes>>(m_shapes)))
{
}

std::shared_ptr<const GroupShape> GroupShape::GetPtr() const
{
	return shared_from_this();
}

RectD GroupShape::GetFrame()
{
	if (m_shapes.size() == 0)
	{
		return { 0, 0, 0, 0 };
	}

	auto frontFrame = m_shapes.front()->GetFrame();
	Point rightBottom = { frontFrame.left + frontFrame.width, frontFrame.top + frontFrame.height };

	RectD result = frontFrame;

	RectD shapeFrame;
	for (auto& shape: m_shapes)
	{
		shapeFrame = shape->GetFrame();
		result.left = std::min(result.left, shapeFrame.left);
		result.top = std::min(result.top, shapeFrame.top);
		if (rightBottom.x < shapeFrame.left + shapeFrame.width)
		{
			rightBottom.x = shapeFrame.left + shapeFrame.width;
		}
		if (rightBottom.y < shapeFrame.top + shapeFrame.height)
		{
			rightBottom.y = shapeFrame.top + shapeFrame.height;
		}
	}

	result.width = rightBottom.x - result.left;
	result.height = rightBottom.y - result.top;

	return result;
}

void GroupShape::SetFrame(const RectD& frame)
{
	auto currFrame = GetFrame();

	auto coefX = frame.width / currFrame.width;
	auto coefY = frame.height / currFrame.height;

	for (auto& shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		auto distanceX = shapeFrame.left - currFrame.left;
		auto distanceY = shapeFrame.top - currFrame.top;

		RectD newShapeFrame = { frame.left + distanceX * coefX,
			frame.top + distanceY * coefY,
			shapeFrame.width * coefX,
			shapeFrame.height * coefY };

		shape->SetFrame(newShapeFrame);
	}
}

std::shared_ptr<ILineStyle> GroupShape::GetLineStyle()
{
	return m_lineStyle;
}

std::shared_ptr<const ILineStyle> GroupShape::GetLineStyle() const
{
	return m_lineStyle;
}

std::shared_ptr<IFillStyle> GroupShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IFillStyle> GroupShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<const IShape> GroupShape::GetGroupShape() const
{
	return GetPtr();
}

size_t GroupShape::GetShapesCount()
{
	return m_shapes.size();
}

std::shared_ptr<IShape> GroupShape::GetShapeAtIndex(size_t index)
{
	return m_shapes.at(index);
}

void GroupShape::InsertShape(std::shared_ptr<IShape> shape, size_t index)
{
	if (m_shapes.size() < index)
	{
		throw std::out_of_range("Index value is out of range");
	}

	m_shapes.insert(m_shapes.begin() + index, shape);
}

void GroupShape::RemoveShapeAtIndex(size_t index)
{
	if (m_shapes.size() <= index)
	{
		throw std::out_of_range("Index value is out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

void GroupShape::Draw(ICanvas& canvas)
{
	for (auto& shape: m_shapes)
	{
		shape->Draw(canvas);
	}
}
