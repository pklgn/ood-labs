#include "../../pch.h"
#include "Display.h"
#include "Tools/AngleTransform.h"

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::Update(double newValue, WeatherEvent event)
{
	std::string eventName;

	switch (event)
	{
	case WeatherEvent::TEMPRATURE:
		eventName = "TEMPRATURE";
		break;
	case WeatherEvent::HUMIDITY:
		eventName = "HUMIDITY";
		break;
	case WeatherEvent::PRESSURE:
		eventName = "PRESSURE";
		break;
	case WeatherEvent::WIND_SPEED:
		eventName = "WIND_SPEED";
		break;
	case WeatherEvent::WIND_ANGLE:
		eventName = "WIND_ANGLE";
		break;
	}

	m_output << eventName << " now is: " << newValue << std::endl;
}