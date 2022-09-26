#include "../../pch.h"
#include "Display.h"

std::string Display::GetLocationToString(Location location)
{
	switch (location)
	{
	case Location::INSIDE:
		return "INSIDE";
	case Location::OUTSIDE:
		return "OUTSIDE";
	case Location::UNKNOWN:
		return "UNKNOWN";
	default:
		return "-";
	}
}

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::Update(SWeatherInfo const& data)
{
	m_output << "Location: " << GetLocationToString(data.location) << std::endl;
	m_output << "Current Temprature: " << data.temperature << std::endl;
	m_output << "Current Humidity: " << data.humidity << std::endl;
	m_output << "Current Pressure: " << data.pressure << std::endl;
	m_output << "------------------" << std::endl;
}
