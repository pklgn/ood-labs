#pragma once

#include "../Dependents/Dependents.hpp"

struct SWindInfo
{
	double speed = 0;
	double angle = 0;
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	SWindInfo wind;
};

enum class WeatherEventType
{
	TEMPRATURE,
	HUMIDITY,
	PRESSURE,
	WIND_SPEED,
	WIND_ANGLE,
};

class WeatherEvent : public IEvent
{
public:
	WeatherEvent(WeatherEventType eventType)
		: m_type(eventType)
	{
	}

	unsigned int GetId() const override
	{
		return static_cast<std::underlying_type<WeatherEventType>::type>(m_type);
	}

private:
	WeatherEventType m_type;
};

class WeatherData : public Publisher<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const;

	// Относительная влажность (0...100)
	double GetHumidity() const;

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const;

	SWindInfo GetWindInfo() const;

	void MeasurementsChanged(const std::vector<WeatherEvent*>&);

	void SetMeasurements(SWeatherInfo&);

protected:
	SWeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_windInfo;
};