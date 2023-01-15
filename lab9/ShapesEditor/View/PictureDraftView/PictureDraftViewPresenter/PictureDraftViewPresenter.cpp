#include "../../../pch.h"
#include "PictureDraftViewPresenter.h"

PictureDraftViewPresenter::PictureDraftViewPresenter(ShapeSelectionModel& selectionModel, PictureDraftView& pictureDraftView, PictureDraftAppModel& pictureDraftModel)
	: m_shapeSelectionModel(selectionModel)
	, m_pictureDraftView(pictureDraftView)
	, m_pictureDraftAppModel(pictureDraftModel)
{
	auto shapeSize = m_pictureDraftAppModel.GetShapeCount();
	for (size_t i = 0; i < shapeSize; ++i)
	{
		auto shape = m_pictureDraftAppModel.GetShape(i);
		auto shapeView = std::make_unique<ShapeView>(shape->GetId(),
			shape->GetFrame(),
			shape->GetType());
		auto shapeViewPresenter = std::make_shared<ShapeViewPresenter>(shape, m_shapeSelectionModel, *shapeView);
		m_shapeViewPresenters.push_back(shapeViewPresenter);
		m_pictureDraftView.AppendShapeView(std::move(shapeView));
	}
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
				IsShapeMouseDown = true;
				if (shapeViewPresenter->GetShapeView().GetId() == shape->GetId())
				{
					shapeViewPresenter->OnMouseDown(point);
					break;
				}
			}
			break;
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
					shapeViewPresenter->OnDrag(offset, point);
					break;
				}
			}
			break;
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
