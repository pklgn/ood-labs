#include "../../pch.h"
#include "StatisticsDisplay.h"

StatisticsDisplay::StatisticsDisplay(std::ostream& output)
	: m_temprature(ComponentType::TEMPRATURE, output)
	, m_humidity(ComponentType::HUMIDITY, output)
	, m_pressure(ComponentType::PRESSURE, output)
	, m_windSpeed(ComponentType::WIND_SPEED, output)
	, m_windAngle(ComponentType::WIND_ANGLE, output)
{
}

void StatisticsDisplay::Update(double newValue, WeatherEvent event)
{
	std::string eventName;

	switch (event)
	{
	case WeatherEvent::TEMPRATURE:
		m_temprature.UpdateData(newValue);
		m_temprature.PrintData();
		break;
	case WeatherEvent::HUMIDITY:
		m_humidity.UpdateData(newValue);
		m_humidity.PrintData();
		break;
	case WeatherEvent::PRESSURE:
		m_pressure.UpdateData(newValue);
		m_pressure.PrintData();
		break;
	case WeatherEvent::WIND_SPEED:
		m_windSpeed.UpdateData(newValue);
		m_windSpeed.PrintData();
		break;
	case WeatherEvent::WIND_ANGLE:
		m_windAngle.UpdateData(newValue);
		m_windAngle.PrintData();
		break;
	}
}