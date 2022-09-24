#include "../pch.h"
#include "WeatherData.h"

WeatherData::WeatherData(Location location)
	: m_location(location)
{
}

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

Location WeatherData::GetLocation() const
{
	return m_location;
}

SWindInfo WeatherData::GetWindInfo() const
{
	return m_windInfo;
}

void WeatherData::MeasurementsChanged()
{
	WeatherData::NotifyObservers();
}

void WeatherData::SetMeasurements(SWeatherWindInfo& weatherWindInfo)
{
	auto& [weatherInfo, windInfo] = weatherWindInfo;
	m_temperature = weatherInfo.temperature;
	m_humidity = weatherInfo.humidity;
	m_pressure = weatherInfo.pressure;
	
	m_windInfo = windInfo;

	MeasurementsChanged();
}

SWeatherInfo WeatherData::GetChangedData() const
{
	SWeatherInfo info;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	info.location = GetLocation();

	return info;
}