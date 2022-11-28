#pragma once
#include "IFillStyle.h"

class AbstractFillStyle : public IFillStyle
{
public:
	AbstractFillStyle(bool isEnabled = true);

	bool IsEnabled() const override;
	void Enable() override;
	void Disable() override;

private:
	bool m_isEnabled;
};
