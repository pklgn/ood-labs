#include "../pch.h"
#include "WeatherData.h"

double WeatherData::GetTemperature() const
{
	return m_temperature;
}

double WeatherData::GetHumidity() const
{
	return m_humidity;
}

double WeatherData::GetPressure() const
{
	return m_pressure;
}

SWindInfo WeatherData::GetWindInfo() const
{
	return m_windInfo;
}

std::vector<WeatherEvent> WeatherData::GetTriggeredEvents(SWeatherInfo& weatherInfo)
{
	std::vector<WeatherEvent> triggeredEvents;

	if (m_temperature != weatherInfo.temperature)
	{
		triggeredEvents.push_back(WeatherEvent::TEMPRATURE);
	}
	if (m_humidity != weatherInfo.humidity)
	{
		triggeredEvents.push_back(WeatherEvent::HUMIDITY);
	}
	if (m_pressure != weatherInfo.pressure)
	{
		triggeredEvents.push_back(WeatherEvent::PRESSURE);
	}
	if (m_windInfo.speed != weatherInfo.wind.speed)
	{
		triggeredEvents.push_back(WeatherEvent::WIND_SPEED);
	}
	if (m_windInfo.angle != weatherInfo.wind.angle)
	{
		triggeredEvents.push_back(WeatherEvent::WIND_ANGLE);
	}

	return triggeredEvents;
}

void WeatherData::MeasurementsChanged(std::vector<WeatherEvent>& triggeredEvents)
{
	for (auto& event : triggeredEvents)
	{
		OnPublish(event);
	}
}

void WeatherData::SetMeasurements(SWeatherInfo& weatherInfo)
{
	std::vector<WeatherEvent> triggeredEvents = GetTriggeredEvents(weatherInfo);

	m_temperature = weatherInfo.temperature;
	m_humidity = weatherInfo.humidity;
	m_pressure = weatherInfo.pressure;

	m_windInfo = weatherInfo.wind;

	MeasurementsChanged(triggeredEvents);
}