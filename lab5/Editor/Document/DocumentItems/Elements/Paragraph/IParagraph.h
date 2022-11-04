#pragma once
#include <string>

#include "../IElement.h"

/* Параграф текста*/
class IParagraph : IElement
{
public:
	virtual std::string GetText() const = 0;

	virtual void SetText(const std::string& text) = 0;
};
