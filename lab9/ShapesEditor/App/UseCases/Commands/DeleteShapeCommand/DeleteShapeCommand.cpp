#include "../../../../pch.h"
#include "DeleteShapeCommand.h"

DeleteShapeCommand::DeleteShapeCommand(const std::shared_ptr<Shape>& shape, const std::shared_ptr<PictureDraft>& pictureDraft, IShapeSelectionModel& selection)
	: m_shape(shape)
	, m_pictureDraft(pictureDraft)
	, m_selectionModel(selection)
{
	auto size = m_pictureDraft->GetShapeCount();
	auto shapeId = m_shape->GetId();
	for (size_t i = 0; i < size; ++i)
	{
		if (shapeId == m_pictureDraft->GetShape(i)->GetId())
		{
			m_index = i;
			break;
		}
	}
}

void DeleteShapeCommand::DoExecute()
{
	m_selectedShapes = m_selectionModel.GetSelectedShapes();
	m_pictureDraft->DeleteShape(m_index);
}

void DeleteShapeCommand::DoUnexecute()
{
	m_pictureDraft->InsertShape(m_shape, m_index);
	m_selectionModel.SetSelectedShapes(m_selectedShapes);
}

