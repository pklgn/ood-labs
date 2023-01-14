#include "../../../pch.h"
#include "ShapeViewPresenter.h"

void ShapeViewPresenter::OnMouseDown(const Point& point)
{
	bool IsPointBelongShape = false;
	auto frame = m_shapeView.GetFrame();
	switch (m_shapeView.GetShapeType())
	{
	case ShapeType::Rectangle:
		IsPointBelongShape = true;
		break;
	case ShapeType::Triangle:
	{
		Point vertex1 = { frame.left, frame.top + frame.height };
		Point vertex2 = { frame.left + frame.width / 2, frame.top };
		Point vertex3 = { frame.left + frame.width, frame.top + frame.height };

		auto sign1 = std::copysign(1, (vertex1.x - point.x) * (vertex2.y - vertex1.y) - (vertex2.x - vertex1.x) * (vertex1.y - point.y));
		auto sign2 = std::copysign(1, (vertex2.x - point.x) * (vertex3.y - vertex2.y) - (vertex3.x - vertex2.x) * (vertex2.y - point.y));
		auto sign3 = std::copysign(1, (vertex3.x - point.x) * (vertex1.y - vertex3.y) - (vertex1.x - vertex3.x) * (vertex3.y - point.y));

		IsPointBelongShape = (sign1 == sign2) && (sign2 == sign3);
	}
		break;
	case ShapeType::Ellipse:
	{
		Point center = { frame.left + frame.width / 2,
			frame.top + frame.height / 2 };
		IsPointBelongShape = pow(point.x - center.x, 2) / pow(frame.width, 2) + pow(point.y - center.y, 2) / pow(frame.height, 2);
	}
		break;
	default:
		break;
	}

	auto selectedShapes = m_shapeSelectionModel.GetSelectedShapes();
	bool IsShapeSelected = std::find_if(selectedShapes.begin(), selectedShapes.end(), [&, this](const std::shared_ptr<ShapeAppModel>& shape) {
		return shape->GetId() == m_shapeAppModel->GetId();
	}) != selectedShapes.end();
	if (IsPointBelongShape &&
		!IsShapeSelected)
	{
		selectedShapes.push_back(m_shapeAppModel);
	}
}
