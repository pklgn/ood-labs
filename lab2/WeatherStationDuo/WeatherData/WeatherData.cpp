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

void WeatherData::MeasurementsChanged()
{
	WeatherData::NotifyObservers();
}

void WeatherData::SetMeasurements(double temp, double humidity, double pressure)
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;

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