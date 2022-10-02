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

void WeatherData::MeasurementsChanged(SWeatherInfo& weatherInfo)
{
	if (m_temperature != weatherInfo.temperature)
	{
		PublishToBroker(WeatherEvent::TEMPRATURE);
	}
	if (m_humidity != weatherInfo.humidity)
	{
		PublishToBroker(WeatherEvent::HUMIDITY);
	}
	if (m_pressure != weatherInfo.pressure)
	{
		PublishToBroker(WeatherEvent::PRESSURE);
	}
	if (m_windInfo.speed != weatherInfo.wind.speed)
	{
		PublishToBroker(WeatherEvent::WIND_SPEED);
	}
	if (m_windInfo.angle != weatherInfo.wind.angle)
	{
		PublishToBroker(WeatherEvent::WIND_ANGLE);
	}
}

void WeatherData::SetMeasurements(SWeatherInfo& weatherInfo)
{
	m_temperature = weatherInfo.temperature;
	m_humidity = weatherInfo.humidity;
	m_pressure = weatherInfo.pressure;

	m_windInfo = weatherInfo.wind;

	MeasurementsChanged(weatherInfo);
}