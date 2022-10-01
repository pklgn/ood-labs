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

void WeatherData::MeasurementsChanged(const std::vector<WeatherEvent*>& eventPtrs)
{
	for (auto& eventPtr : eventPtrs)
	{
		WeatherData::NotifyObservers(eventPtr);
	}
}

void WeatherData::SetMeasurements(SWeatherInfo& weatherInfo)
{
	std::vector<WeatherEvent*> invokedEventPtrs;
	if (m_temperature != weatherInfo.temperature)
	{
		invokedEventPtrs.push_back(new WeatherEvent(WeatherEventType::TEMPRATURE));
	}
	m_temperature = weatherInfo.temperature;

	if (m_humidity != weatherInfo.humidity)
	{
		invokedEventPtrs.push_back(new WeatherEvent(WeatherEventType::HUMIDITY));
	}
	m_humidity = weatherInfo.humidity;

	if (m_pressure != weatherInfo.pressure)
	{
		invokedEventPtrs.push_back(new WeatherEvent(WeatherEventType::PRESSURE));
	}
	m_pressure = weatherInfo.pressure;

	if (m_windInfo.speed != weatherInfo.wind.speed)
	{
		invokedEventPtrs.push_back(new WeatherEvent(WeatherEventType::WIND_SPEED));
	}

	if (m_windInfo.angle != weatherInfo.wind.angle)
	{
		invokedEventPtrs.push_back(new WeatherEvent(WeatherEventType::WIND_SPEED));
	}
	m_windInfo = weatherInfo.wind;

	MeasurementsChanged(invokedEventPtrs);
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