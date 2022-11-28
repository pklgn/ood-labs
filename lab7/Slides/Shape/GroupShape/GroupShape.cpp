#include "../../pch.h"
#include "GroupShape.h"
#include "../../Style/LineStyle/Enumerator/LineStyleEnumerator.hpp"
#include "../../Style/FillStyle/Enumerator/FillStyleEnumerator.hpp"

typedef std::vector<std::shared_ptr<IShape>> Shapes;

GroupShape::GroupShape(Shapes shapes)
	: m_shapes(shapes)
	, m_lineStyle(std::make_shared<CompositeLineStyle>(std::make_unique<LineStyleEnumerator<Shapes>>(shapes)))
	, m_fillStyle(std::make_shared<CompositeFillStyle>(std::make_unique<FillStyleEnumerator<Shapes>>(shapes)))
{
	m_frame = GetFrame();
}

std::shared_ptr<GroupShape> GroupShape::GetPtr()
{
	return shared_from_this();
}

std::shared_ptr<const GroupShape> GroupShape::GetPtr() const
{
	return shared_from_this();
}

RectD GroupShape::GetFrame()
{
	//TODO: refactor this
	if (m_shapes.size() == 0)
	{
		m_frame = { m_frame.left, m_frame.top, 0, 0 };

		return m_frame;
	}

	auto frontFrame = m_shapes.front()->GetFrame();
	Point rightBottom = { frontFrame.left, frontFrame.top };

	RectD result{ frontFrame.left, frontFrame.top, 0, 0 };

	for (auto& shape: m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
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
	m_frame = frame;
}

std::shared_ptr<ILineStyle> GroupShape::GetLineStyle()
{
	return m_lineStyle;
}

std::shared_ptr<const ILineStyle> GroupShape::GetLineStyle() const
{
	return m_lineStyle;
}

void GroupShape::SetLineStyle(std::shared_ptr<ILineStyle> style)
{
	if (style->GetColor().has_value())
	{
		m_lineStyle->SetColor(style->GetColor().value());
	}

	if (style->GetThickness().has_value())
	{
		m_lineStyle->SetThickness(style->GetThickness().value());
	}

	if (m_lineStyle->IsEnabled() != style->IsEnabled())
	{
		if (m_lineStyle->IsEnabled())
		{
			m_lineStyle->Disable();
		}
		else
		{
			m_lineStyle->Enable();
		}
	}
}

std::shared_ptr<IFillStyle> GroupShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IFillStyle> GroupShape::GetFillStyle() const
{
	return m_fillStyle;
}

void GroupShape::SetFillStyle(std::shared_ptr<IFillStyle> style)
{
	if (style->GetColor().has_value())
	{
		m_fillStyle->SetColor(style->GetColor().value());
	}

	if (m_fillStyle->IsEnabled() != style->IsEnabled())
	{
		if (m_fillStyle->IsEnabled())
		{
			m_fillStyle->Disable();
		}
		else
		{
			m_fillStyle->Enable();
		}
	}
}

std::shared_ptr<const IShape> GroupShape::GetGroupShape() const
{
	return GetPtr();
}
