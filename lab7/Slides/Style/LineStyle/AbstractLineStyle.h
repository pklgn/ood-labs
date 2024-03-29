#pragma once
#include "ILineStyle.h"

class AbstractLineStyle : public ILineStyle
{
public:
	AbstractLineStyle(bool isEnabled = true);

	bool IsEnabled() const override;
	void Enable() override;
	void Disable() override;

protected:
	bool m_isEnabled;
};