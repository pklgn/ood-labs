#include "../../../../pch.h"
#include "InsertShapeCommand.h"

InsertShapeCommand::InsertShapeCommand(size_t index, const std::shared_ptr<Shape>& shape, const std::shared_ptr<PictureDraft>& pictureDraft, IShapeSelectionModel& selection)
	: m_index(index)
	, m_shape(shape)
	, m_pictureDraft(pictureDraft)
	, m_selectionModel(selection)
{
}

void InsertShapeCommand::DoExecute()
{
	m_selectedShapes = m_selectionModel.GetSelectedShapes();
	m_pictureDraft->InsertShape(m_shape, m_index);
}

void InsertShapeCommand::DoUnexecute()
{
	m_pictureDraft->DeleteShape(m_index);
	m_selectionModel.SetSelectedShapes(m_selectedShapes);
}
