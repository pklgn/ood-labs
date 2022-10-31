#pragma once
#include <string>

#include "../DocumentItems/IBaseDocumentItem.h"

/* Параграф текста*/
class IParagraph : public IBaseDocumentItem
{
public:
	virtual std::string GetText() const = 0;

	virtual void SetText(const std::string& text) = 0;
	//virtual ~IParagraph() = default;
};
