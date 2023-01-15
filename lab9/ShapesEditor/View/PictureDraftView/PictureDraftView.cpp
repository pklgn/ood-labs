#include "../../pch.h"
#include "PictureDraftView.h"

PictureDraftView::PictureDraftView(PictureDraftAppModel& pictureDraft, ShapeSelectionModel& shapeSelection)
	: m_pictureDraftAppModel(pictureDraft)
	, m_shapeSelectionModel(shapeSelection)
{
	m_shapeSelectionModel.DoOnSelectionChanged([&, this](const std::vector<std::shared_ptr<ShapeAppModel>>& selectedShapes) mutable {
		m_selectionFramesView.clear();
		for (auto&& shape : selectedShapes)
		{
			std::cout << "@@@@@@@@@@@@@@@@DoOnSelectionChanged\n";
			m_selectionFramesView.push_back(SelectionFrameView(*shape));
			std::cout << std::addressof(m_selectionFramesView.back());
		}
	});
}

void PictureDraftView::InsertSelectionFrame(ShapeAppModel& shape)
{
	m_selectionFramesView.push_back(SelectionFrameView(shape));
}

void PictureDraftView::DeleteSelectionFrame()
{
	m_selectionFramesView.clear();
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
		std::cout << "PictureDraftView " << std::addressof(selectionFrame) << std::endl;
		
	}
}

void PictureDraftView::SetListener(const std::shared_ptr<IPictureDraftViewListener>& listener)
{
	m_listener = listener;
}

void PictureDraftView::AppendShapeView(std::unique_ptr<ShapeView>&& shapeView)
{
	std::cout << "AppendShapeView " << std::addressof(shapeView);
	m_shapesView.push_back(std::move(shapeView));
}
