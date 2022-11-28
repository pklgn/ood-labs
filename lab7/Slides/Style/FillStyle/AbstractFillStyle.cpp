#include "../../pch.h"
#include "AbstractFillStyle.h"

AbstractFillStyle::AbstractFillStyle(bool isEnabled)
	: m_isEnabled(isEnabled)
{
}

bool AbstractFillStyle::IsEnabled() const
{
	return m_isEnabled;
}

void AbstractFillStyle::Enable()
{
	if (m_isEnabled)
	{
		throw std::logic_error("Line style has been already enabled");
	}

	m_isEnabled = true;
}

void AbstractFillStyle::Disable()
{
	if (!m_isEnabled)
	{
		throw std::logic_error("Line style has been already disabled");
	}

	m_isEnabled = false;
}