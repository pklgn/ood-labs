#include "../pch.h"
#include "Designer.h"
#include "../Shapes/Factory/ShapeFactory.h"

Designer::Designer()
	: m_shapeFactory(std::make_unique<ShapeFactory>())
{
}

PictureDraft Designer::CreateDraft(std::istream& is)
{
	PictureDraft pictureDraft;

	std::string description;
	while (std::getline(is, description))
	{
		pictureDraft.AddShape(m_shapeFactory->CreateShape(description));
	}

	return pictureDraft;
}
