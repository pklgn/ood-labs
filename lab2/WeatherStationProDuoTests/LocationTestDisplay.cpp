#include "LocationTestDisplay.h"

LocationTestDisplay::LocationTestDisplay(std::ostream& output)
	: Display(output)
{
}

void LocationTestDisplay::Update(SWeatherInfo const& data)
{
	std::string locationString;
	if (data.version == Version::BASIC)
	{
		locationString = "INSIDE";
	}
	else if (data.version == Version::PRO)
	{
		locationString = "OUTSIDE";
	}
	else
	{
		locationString = "UNKNOWN";
	}

	m_output << locationString;
}
