#include "../../pch.h"
#include "PictureDraftView.h"

PictureDraftView::PictureDraftView(PictureDraftAppModel& pictureDraft, ShapeSelectionModel& shapeSelection, size_t width, size_t height)
	: m_pictureDraftAppModel(pictureDraft)
	, m_shapeSelectionModel(shapeSelection)
	, m_width(width)
	, m_height(height)
{
	m_shapeSelectionModel.DoOnSelectionChanged([&, this](const std::vector<std::shared_ptr<ShapeAppModel>>& selectedShapes) mutable {
		m_selectionFramesView.clear();
		for (auto&& shape : selectedShapes)
		{
			m_selectionFramesView.push_back(SelectionFrameView(*shape));
		}
	});
}

void PictureDraftView::Show(ICanvas& canvas)
{
	for (auto&& shape : m_shapesView)
	{
		shape->Show(canvas);
	}

	for (auto&& selectionFrame : m_selectionFramesView)
	{
		selectionFrame.Show(canvas);
		
	}
}

void PictureDraftView::InsertShapeView(size_t index, std::unique_ptr<ShapeView>&& shapeView)
{
	m_shapesView.insert(m_shapesView.begin() + index, std::move(shapeView));
}

void PictureDraftView::DeleteShapeView(size_t index)
{
	m_shapesView.erase(m_shapesView.begin() + index);
}

size_t PictureDraftView::GetWidth() const
{
	return m_width;
}

size_t PictureDraftView::GetHeight() const
{
	return m_height;
}
