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
	PictureDraftView(PictureDraftAppModel&, ShapeSelectionModel&);
	
	void InsertSelectionFrame(ShapeAppModel&);
	void DeleteSelectionFrame();
	void Show(ICanvas&) override;
	void SetListener(const std::shared_ptr<IPictureDraftViewListener>&);
	void AppendShapeView(std::unique_ptr<ShapeView>&&);

private:
	std::vector<std::unique_ptr<ShapeView>> m_shapesView;
	std::vector<SelectionFrameView> m_selectionFramesView;
	PictureDraftAppModel& m_pictureDraftAppModel;
	ShapeSelectionModel& m_shapeSelectionModel;
	std::shared_ptr<IPictureDraftViewListener> m_listener;
};