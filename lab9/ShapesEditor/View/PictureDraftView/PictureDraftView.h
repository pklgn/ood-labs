#pragma once
#include "../../App/PictureDraftAppModel/PictureDraftAppModel.h"
#include "../../App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../IView.h"
#include "../SelectionFrameView/SelectionFrameView.h"
#include "../ShapeView/ShapeView.h"
#include "IPictureDraftViewListener.h"

class PictureDraftView : public IView
{
public:
	PictureDraftView(PictureDraftAppModel&, ShapeSelectionModel&, size_t width, size_t height);
	
	void Show(ICanvas&) override;

	void InsertShapeView(size_t, std::shared_ptr<ShapeView>&&);
	void DeleteShapeView(size_t);
	size_t GetWidth() const;
	size_t GetHeight() const;

private:
	std::vector<std::shared_ptr<ShapeView>> m_shapesView;
	std::vector<SelectionFrameView> m_selectionFramesView;
	PictureDraftAppModel& m_pictureDraftAppModel;
	ShapeSelectionModel& m_shapeSelectionModel;
	size_t m_width;
	size_t m_height;
};