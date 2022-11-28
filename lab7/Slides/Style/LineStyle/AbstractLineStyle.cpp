#include "../../pch.h"
#include "AbstractLineStyle.h"

AbstractLineStyle::AbstractLineStyle(bool isEnabled)
	: m_isEnabled(isEnabled)
{
}

bool AbstractLineStyle::IsEnabled() const
{
	return m_isEnabled;
}

void AbstractLineStyle::Enable()
{
	if (m_isEnabled)
	{
		throw std::logic_error("Line style has been already enabled");
	}

	m_isEnabled = true;
}

void AbstractLineStyle::Disable()
{
	if (!m_isEnabled)
	{
		throw std::logic_error("Line style has been already disabled");
	}

	m_isEnabled = false;
}
