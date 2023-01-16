#include "../../../pch.h"
#include "PictureDraftViewPresenter.h"

PictureDraftViewPresenter::PictureDraftViewPresenter(ShapeSelectionModel& selectionModel, PictureDraftView& pictureDraftView, PictureDraftAppModel& pictureDraftModel, IHistory& history)
	: m_shapeSelectionModel(selectionModel)
	, m_pictureDraftView(pictureDraftView)
	, m_pictureDraftAppModel(pictureDraftModel)
	, m_history(history)
{
	auto shapeSize = m_pictureDraftAppModel.GetShapeCount();
	for (size_t i = 0; i < shapeSize; ++i)
	{
		SetupShapeView(i);
	}

	m_pictureDraftAppModel.DoOnShapeAdded([this](size_t index) {
		SetupShapeView(index);
	});
}

void PictureDraftViewPresenter::OnMouseDown(const Point& point)
{
	auto shapesSize = m_pictureDraftAppModel.GetShapeCount();
	if (shapesSize == 0)
	{
		return;
	}
	auto IsShapeMouseDown = false;
	for (int i = shapesSize - 1; i >= 0; --i)
	{
		auto shape = m_pictureDraftAppModel.GetShape(i);
		auto frame = shape->GetFrame();
		if (frame.left <= point.x && point.x <= frame.left + frame.width &&
			frame.top <= point.y && point.y <= frame.top + frame.height)
		{
			for (auto&& shapeViewPresenter : m_shapeViewPresenters)
			{
				if (shapeViewPresenter->GetShapeView().GetId() == shape->GetId())
				{
					shapeViewPresenter->OnMouseDown(point);
					auto selectedShapes = m_shapeSelectionModel.GetSelectedShapes();
					if (selectedShapes.size() != 0 &&
						selectedShapes.back()->GetId() == shape->GetId() )
					{
						IsShapeMouseDown = true;
						break;
					}
				}
			}
			if (IsShapeMouseDown)
			{
				break;
			}
		}
	}
	if (!IsShapeMouseDown)
	{
		m_shapeSelectionModel.SetSelectedShapes({});
	}
}

void PictureDraftViewPresenter::OnDrag(const Point& offset, const Point& point)
{
	auto shapesSize = m_pictureDraftAppModel.GetShapeCount();
	if (shapesSize == 0)
	{
		return;
	}
	auto selectedShapes = m_shapeSelectionModel.GetSelectedShapes();
	for (int i = shapesSize - 1; i >= 0; --i)
	{
		auto shape = m_pictureDraftAppModel.GetShape(i);
		auto frame = shape->GetFrame();
		if (frame.left <= point.x && point.x <= frame.left + frame.width &&
			frame.top <= point.y && point.y <= frame.top + frame.height)
		{
			for (auto&& shapeViewPresenter : m_shapeViewPresenters)
			{
				if (shapeViewPresenter->GetShapeView().GetId() == shape->GetId() &&
					std::find_if(selectedShapes.begin(), selectedShapes.end(), [&, shape](const std::shared_ptr<ShapeAppModel>& currShape) {
						return currShape->GetId() == shape->GetId();
					}) != selectedShapes.end())
				{
					shapeViewPresenter->OnDrag(offset, point);
					break;
				}
			}
		}
	}
}

void PictureDraftViewPresenter::OnMouseUp(const Point& point)
{
	auto shapesSize = m_pictureDraftAppModel.GetShapeCount();
	if (shapesSize == 0)
	{
		return;
	}
	for (int i = shapesSize - 1; i >= 0; --i)
	{
		auto shape = m_pictureDraftAppModel.GetShape(i);
		auto frame = shape->GetFrame();
		if (frame.left <= point.x && point.x <= frame.left + frame.width && frame.top <= point.y && point.y <= frame.top + frame.height)
		{
			for (auto&& shapeViewPresenter : m_shapeViewPresenters)
			{
				if (shapeViewPresenter->GetShapeView().GetId() == shape->GetId())
				{
					shapeViewPresenter->OnMouseUp(point);
					break;
				}
			}
			break;
		}
	}
}

void PictureDraftViewPresenter::InsertShape(ShapeType type)
{
	auto useCase = m_pictureDraftAppModel.CreateInsertShapeUseCase();
	auto index = m_pictureDraftAppModel.GetShapeCount();
	useCase->Insert(index, type);
}

void PictureDraftViewPresenter::DeleteShape()
{
	auto useCase = m_shapeSelectionModel.CreateDeleteShapeUseCase(m_pictureDraftAppModel);
	useCase->Delete();
}

void PictureDraftViewPresenter::Undo()
{
	m_history.Undo();
}

void PictureDraftViewPresenter::Redo()
{
	m_history.Redo();
}

void PictureDraftViewPresenter::SetupShapeView(size_t index)
{
	auto shape = m_pictureDraftAppModel.GetShape(index);
	auto shapeView = std::make_unique<ShapeView>(shape->GetId(),
		shape->GetFrame(),
		shape->GetType());
	auto shapeViewPresenter = std::make_shared<ShapeViewPresenter>(shape, m_shapeSelectionModel, *shapeView);
	shapeViewPresenter->SetRespectFrameBorders(m_pictureDraftView.GetWidth(), m_pictureDraftView.GetHeight());
	m_shapeViewPresenters.push_back(shapeViewPresenter);
	m_pictureDraftView.AppendShapeView(std::move(shapeView));
}

