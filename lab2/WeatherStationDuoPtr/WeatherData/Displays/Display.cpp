#include "../../pch.h"
#include "Display.h"

Display::Display(std::ostream& output, ObservablePtrType weatherInside, ObservablePtrType weatherOutside)
	: m_output(output)
	, m_weatherObservableInside(weatherInside)
	, m_weatherObservableOutside(weatherOutside)
{
}

void Display::Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable)
{
	PrintLocation(observable);
	m_output << "Current Temprature: " << data.temperature << std::endl;
	m_output << "Current Humidity: " << data.humidity << std::endl;
	m_output << "Current Pressure: " << data.pressure << std::endl;
	m_output << "------------------" << std::endl;
}

void Display::PrintLocation(IObservable<SWeatherInfo> const& observable)
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

	m_output << "Location: " << locationString << std::endl;
}
