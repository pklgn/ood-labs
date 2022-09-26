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

void WeatherData::MeasurementsChanged()
{
	WeatherData::NotifyObservers();
}

void WeatherData::SetMeasurements(SWeatherInfo& weatherInfo)
{
	m_temperature = weatherInfo.temperature;
	m_humidity = weatherInfo.humidity;
	m_pressure = weatherInfo.pressure;

	MeasurementsChanged();
}

SWeatherInfo WeatherData::GetChangedData() const
{
	SWeatherInfo info;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();

	return info;
}

void WeatherDataPro::SetMeasurements(SWeatherInfo& weatherInfo)
{
	m_temperature = weatherInfo.temperature;
	m_humidity = weatherInfo.humidity;
	m_pressure = weatherInfo.pressure;
	m_windInfo = weatherInfo.wind;

	MeasurementsChanged();
}

SWeatherInfo WeatherDataPro::GetChangedData() const
{
	SWeatherInfo info;
	info.version = Version::PRO;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	info.wind = GetWindInfo();

	return info;
}

SWindInfo WeatherDataPro::GetWindInfo() const
{
	return m_windInfo;
}