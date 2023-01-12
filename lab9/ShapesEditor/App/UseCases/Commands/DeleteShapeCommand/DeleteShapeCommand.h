#pragma once
#include "../../../Command/AbstractCommand.h"
#include "../../../../model/Shape/Shape.h"
#include "../../../../model/PictureDraft/PictureDraft.h"

class DeleteShapeCommand : public AbstractCommand
{
public:
	DeleteShapeCommand(const std::shared_ptr<Shape>&, const std::shared_ptr<PictureDraft>&);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<Shape> m_shape;
	std::shared_ptr<PictureDraft> m_pictureDraft;
	size_t m_index = SIZE_MAX;
};