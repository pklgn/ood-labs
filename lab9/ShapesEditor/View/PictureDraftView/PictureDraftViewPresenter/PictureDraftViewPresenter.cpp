#include "../../../pch.h"
#include "PictureDraftViewPresenter.h"

PictureDraftViewPresenter::PictureDraftViewPresenter(ShapeSelectionModel& selectionModel, PictureDraftView& pictureDraftView, PictureDraftAppModel& pictureDraftModel, IUseCaseFactory& useCaseFactory)
	: m_shapeSelectionModel(selectionModel)
	, m_pictureDraftView(pictureDraftView)
	, m_pictureDraftAppModel(pictureDraftModel)
	, m_useCaseFactory(useCaseFactory)
{
	auto shapeSize = m_pictureDraftAppModel.GetShapeCount();
	for (size_t i = 0; i < shapeSize; ++i)
	{
		SetupShapeView(i);
	}

	m_pictureDraftAppModel.DoOnShapeAdded([this](size_t index) {
		SetupShapeView(index);
		m_shapeSelectionModel.SetSelectedShapes({ m_pictureDraftAppModel.GetShape(index) });
	});

	m_pictureDraftAppModel.DoOnShapeDeleted([this](size_t index, std::shared_ptr<ShapeAppModel> shape) {
		CleanUpShapeView(index, shape);
		m_shapeSelectionModel.SetSelectedShapes({});
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
				if (shapeViewPresenter->GetShapeView()->GetId() == shape->GetId())
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
				if (shapeViewPresenter->GetShapeView()->GetId() == shape->GetId() &&
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
				if (shapeViewPresenter->GetShapeView()->GetId() == shape->GetId())
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
	auto useCase = m_useCaseFactory.CreateInsertShapeUseCase(m_pictureDraftAppModel);
	auto index = m_pictureDraftAppModel.GetShapeCount();
	useCase->Insert(index, type);
}

void PictureDraftViewPresenter::DeleteShape()
{
	auto useCase = m_useCaseFactory.CreateDeleteShapeUseCase(m_pictureDraftAppModel);
	useCase->Delete();
}

void PictureDraftViewPresenter::Undo()
{
	m_pictureDraftAppModel.Undo();
}

void PictureDraftViewPresenter::Redo()
{
	m_pictureDraftAppModel.Redo();
}

void PictureDraftViewPresenter::SetupShapeView(size_t index)
{
	auto shape = m_pictureDraftAppModel.GetShape(index);
	auto shapeView = std::make_shared<ShapeView>(shape->GetId(),
		shape->GetFrame(),
		shape->GetType());
	auto shapeViewPresenter = std::make_shared<ShapeViewPresenter>(shape, m_useCaseFactory, m_shapeSelectionModel, shapeView);
	shapeViewPresenter->SetRespectFrameBorders(m_pictureDraftView.GetWidth(), m_pictureDraftView.GetHeight());
	m_shapeViewPresenters.push_back(shapeViewPresenter);
	m_pictureDraftView.InsertShapeView(index, std::move(shapeView));
}

void PictureDraftViewPresenter::CleanUpShapeView(size_t index, const std::shared_ptr<ShapeAppModel>& shape)
{
	auto id = shape->GetId();
	m_shapeViewPresenters.erase(std::find_if(m_shapeViewPresenters.begin(), m_shapeViewPresenters.end(),
		[&id](const std::shared_ptr<ShapeViewPresenter>& presenter) {
			return presenter->GetShapeView()->GetId() == id;
		}));
	m_pictureDraftView.DeleteShapeView(index);
}

