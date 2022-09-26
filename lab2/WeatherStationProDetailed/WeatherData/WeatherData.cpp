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
	if (weatherInfo.temperature.has_value())
	{
		PublishToBroker(WeatherEvent::TEMPRATURE, weatherInfo.temperature.value());
	}
	if (weatherInfo.humidity.has_value())
	{
		PublishToBroker(WeatherEvent::HUMIDITY, weatherInfo.humidity.value());
	}
	if (weatherInfo.pressure.has_value())
	{
		PublishToBroker(WeatherEvent::PRESSURE, weatherInfo.pressure.value());
	}
	if (weatherInfo.wind.has_value())
	{
		PublishToBroker(WeatherEvent::WIND_SPEED, weatherInfo.wind.value().speed);
	}
	if (weatherInfo.wind.has_value())
	{
		PublishToBroker(WeatherEvent::WIND_ANGLE, weatherInfo.wind.value().angle);
	}
}

void WeatherData::SetMeasurements(SWeatherInfo& weatherInfo)
{
	m_temperature = weatherInfo.temperature.value_or(m_temperature);
	m_humidity = weatherInfo.humidity.value_or(m_humidity);
	m_pressure = weatherInfo.pressure.value_or(m_pressure);

	m_windInfo = weatherInfo.wind.value_or(m_windInfo);

	MeasurementsChanged(weatherInfo);
}

SWeatherInfo WeatherData::GetChangedData() const
{
	SWeatherInfo info;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	info.wind = GetWindInfo();

	return info;
}