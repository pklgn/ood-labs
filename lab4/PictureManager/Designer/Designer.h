#pragma once
#include "IDesigner.h"
#include "../Shapes/Factory/IShapeFactory.h"

class Designer : public IDesigner
{
public:
	Designer();

	PictureDraft CreateDraft(std::istream&) override;

private:
	std::unique_ptr<IShapeFactory> m_shapeFactory;
};
