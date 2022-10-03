#pragma once

#include <optional>
#include "../pch.h"
#include "../Dependents/Dependents.hpp"

enum class WeatherEvent
{
	TEMPRATURE,
	PRESSURE,
	HUMIDITY,
	WIND_SPEED,
	WIND_ANGLE,
	NO_EVENT,
};

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

class WeatherData : public Broker<WeatherEvent>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const;

	// Относительная влажность (0...100)
	double GetHumidity() const;

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const;

	SWindInfo GetWindInfo() const;

	std::vector<WeatherEvent> GetTriggeredEvents(SWeatherInfo&);

	void MeasurementsChanged(std::vector<WeatherEvent>&);

	void SetMeasurements(SWeatherInfo&);

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_windInfo;
};
