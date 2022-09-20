#include "../../pch.h"
#include "Display.h"

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable)
{
	switch (data.location)
	{
	case Location::INDOORS:
		m_output << "IN\n";
		break;
	case Location::OUTDOORS:
		m_output << "OUT\n";
		break;
	}

	m_output << "Current Temprature: " << data.temperature << std::endl;
	m_output << "Current Humidity: " << data.humidity << std::endl;
	m_output << "Current Pressure: " << data.pressure << std::endl;
	m_output << "------------------" << std::endl;
}