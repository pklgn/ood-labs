#pragma once
#include <istream>
#include "../PictureDraft/PictureDraft.h"

class IDesigner
{
public:
	virtual PictureDraft CreateDraft(std::istream&) = 0;

	virtual ~IDesigner() = default;
};