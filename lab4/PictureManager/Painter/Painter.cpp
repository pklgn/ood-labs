#include "../pch.h"
#include "Painter.h"

void Painter::DrawPicture(const PictureDraft& pictureDraft, ICanvas& canvas)
{
	for (auto& shapePtr : pictureDraft)
	{
		shapePtr->Draw(canvas);
	}
}
