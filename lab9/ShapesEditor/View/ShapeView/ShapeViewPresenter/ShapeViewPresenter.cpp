#include "../../../pch.h"
#include "ShapeViewPresenter.h"

const size_t DEFAULT_SELECTION_CORNER_SIZE = 10;

ShapeViewPresenter::ShapeViewPresenter(const std::shared_ptr<ShapeAppModel>& model, ShapeSelectionModel& selectionModel, ShapeView& shapeView)
	: m_shapeAppModel(model)
	, m_shapeSelectionModel(selectionModel)
	, m_shapeView(shapeView)
{
	m_shapeAppModel->DoOnFrameChanged([&, this](const RectD& frame) {
		m_shapeView.SetFrame(frame);
	});
}

const ShapeView& ShapeViewPresenter::GetShapeView() const
{
	return m_shapeView;
}

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
		IsPointBelongShape = (pow(point.x - center.x, 2) / pow(frame.width / 2, 2) +
			pow(point.y - center.y, 2) / pow(frame.height / 2, 2)) <= 1;
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
		m_shapeSelectionModel.SetSelectedShapes({ m_shapeAppModel });
	}
}

void ShapeViewPresenter::OnDrag(const Point& offset, const Point& point)
{
	auto frame = m_shapeAppModel->GetFrame();
	auto useCase = m_shapeSelectionModel.CreateResizeShapeUseCase();
	if (IsOnCorner({ frame.left, frame.top }, point))
	{
		useCase->Resize(offset, BasePoint::RightBottom);
	}
	else if (IsOnCorner({ frame.left + frame.width - DEFAULT_SELECTION_CORNER_SIZE, frame.top }, point))
	{
		useCase->Resize(offset, BasePoint::LeftBottom);
	}
	else if (IsOnCorner({ frame.left + frame.width - DEFAULT_SELECTION_CORNER_SIZE, frame.top + frame.height - DEFAULT_SELECTION_CORNER_SIZE }, point))
	{
		useCase->Resize(offset, BasePoint::LeftTop);
	}
	else if (IsOnCorner({ frame.left, frame.top + frame.height - DEFAULT_SELECTION_CORNER_SIZE }, point))
	{
		useCase->Resize(offset, BasePoint::RightTop);
	}
	else
	{
		auto useCase = m_shapeSelectionModel.CreateMoveShapeUseCase();
		useCase->Move(offset);
	}
	
	auto selectedShapes = m_shapeSelectionModel.GetSelectedShapes();
	for (auto&& shape : selectedShapes)
	{
		RespectFrameBorders(shape);
	}
}

void ShapeViewPresenter::OnMouseUp(const Point& point)
{
	auto frame = m_shapeAppModel->GetFrame();
	if (IsOnCorner({ frame.left, frame.top }, point) ||
		IsOnCorner({ frame.left + frame.width - DEFAULT_SELECTION_CORNER_SIZE, frame.top }, point) ||
		IsOnCorner({ frame.left + frame.width - DEFAULT_SELECTION_CORNER_SIZE, frame.top + frame.height - DEFAULT_SELECTION_CORNER_SIZE }, point) ||
		IsOnCorner({ frame.left, frame.top + frame.height - DEFAULT_SELECTION_CORNER_SIZE }, point))
	{
		auto useCase = m_shapeSelectionModel.CreateResizeShapeUseCase();
		useCase->Commit();
	}
	else
	{
		auto useCase = m_shapeSelectionModel.CreateMoveShapeUseCase();
		useCase->Commit();
	}
}

void ShapeViewPresenter::SetRespectFrameBorders(size_t width, size_t height)
{
	m_respectFrameWidth = width;
	m_respectFrameHeight = height;
}

bool ShapeViewPresenter::IsOnCorner(const Point& leftTop, const Point& point)
{
	return (leftTop.x <= point.x && point.x <= leftTop.x + DEFAULT_SELECTION_CORNER_SIZE &&
		leftTop.y <= point.y && point.y <= leftTop.y + DEFAULT_SELECTION_CORNER_SIZE);
}

void ShapeViewPresenter::RespectFrameBorders(const std::shared_ptr<ShapeAppModel>& shape)
{
	bool frameChanged = false;
	auto frame = shape->GetFrame();
	if (frame.left < 0)
	{
		frameChanged = true;
		frame.left = 0;
	}
	if (frame.top < 0)
	{
		frameChanged = true;
		frame.top = 0;
	}
	if (m_respectFrameWidth < frame.width)
	{
		frameChanged = true;
		frame.width = m_respectFrameWidth;
	}
	if (m_respectFrameHeight < frame.height)
	{
		frameChanged = true;
		frame.height = m_respectFrameHeight;
	}
	if (m_respectFrameWidth - frame.width < frame.left)
	{
		frameChanged = true;
		frame.left = m_respectFrameWidth - frame.width;
	}
	if (m_respectFrameHeight - frame.height < frame.top)
	{
		frameChanged = true;
		frame.top = m_respectFrameHeight - frame.height;
	}
	if (frameChanged)
	{
		shape->SetFrame(frame);
	}
}

