#pragma once
#include "../../../Command/AbstractCommand.h"
#include "../../../../model/Shape/Shape.h"
#include "../../../../model/PictureDraft/PictureDraft.h"
#include "../../../ShapeSelectionModel/IShapeSelectionModel.h"

class InsertShapeCommand : public AbstractCommand
{
public:
	InsertShapeCommand(size_t index, const std::shared_ptr<Shape>&, const std::shared_ptr<PictureDraft>&, IShapeSelectionModel&);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<Shape> m_shape;
	std::shared_ptr<PictureDraft> m_pictureDraft;
	IShapeSelectionModel& m_selectionModel;
	size_t m_index;
	std::vector<std::shared_ptr<ShapeAppModel>> m_selectedShapes;
};