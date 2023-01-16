#include "../../../../pch.h"
#include "InsertShapeCommand.h"

InsertShapeCommand::InsertShapeCommand(size_t index, const std::shared_ptr<Shape>& shape, const std::shared_ptr<PictureDraft>& pictureDraft)
	: m_index(index)
	, m_shape(shape)
	, m_pictureDraft(pictureDraft)
{
}

void InsertShapeCommand::DoExecute()
{
	m_pictureDraft->InsertShape(m_shape, m_index);
}

void InsertShapeCommand::DoUnexecute()
{
	m_pictureDraft->DeleteShape(m_index);
}
