#include "LocationTestDisplay.h"

LocationTestDisplay::LocationTestDisplay(std::ostream& output)
	: Display(output)
{
}

void LocationTestDisplay::Update(SWeatherInfo const& data)
{
	m_output << GetLocationToString(data.location);
}
