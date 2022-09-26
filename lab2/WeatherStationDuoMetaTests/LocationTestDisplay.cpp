#include "LocationTestDisplay.h"

LocationTestDisplay::LocationTestDisplay(std::ostream& output)
	: Display(output)
{
}

void LocationTestDisplay::Update(SWeatherInfo const& data, Location const& location)
{
	switch (location)
	{
	case Location::INSIDE:
		m_output << "INSIDE";
		break;
	case Location::OUTSIDE:
		m_output << "OUTSIDE";
		break;
	default:
		m_output << "ERROR";
		break;
	}
}
