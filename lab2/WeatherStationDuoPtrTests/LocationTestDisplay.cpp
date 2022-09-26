#include "LocationTestDisplay.h"

LocationTestDisplay::LocationTestDisplay(std::ostream& output, ObservablePtrType weatherInside, ObservablePtrType weatherOutside)
	: Display(output, weatherInside, weatherOutside)
{
}

void LocationTestDisplay::Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable)
{
	std::string locationString;
	if (&observable == m_weatherObservableInside)
	{
		locationString = "INSIDE";
	}
	else if (&observable == m_weatherObservableOutside)
	{
		locationString = "OUTSIDE";
	}
	else
	{
		locationString = "UNKNOWN";
	}

	m_output << locationString;
}
