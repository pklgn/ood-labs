#pragma once

#include "../pch.h"
#include "../Dependents/Dependents.hpp"

enum class Location
{
	INSIDE,
	OUTSIDE,
	UNKNOWN,
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
	Location location = Location::UNKNOWN;
};

struct SWeatherWindInfo
{
	SWeatherInfo weatherInfo;
	SWindInfo windInfo;
};

class WeatherData : public Observable<SWeatherInfo>
{
public:
	WeatherData(Location location);

	// Температура в градусах Цельсия
	double GetTemperature() const;

	// Относительная влажность (0...100)
	double GetHumidity() const;

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const;

	Location GetLocation() const;

	SWindInfo GetWindInfo() const;

	void MeasurementsChanged();

	void SetMeasurements(SWeatherWindInfo&);

protected:
	SWeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	Location m_location;
	SWindInfo m_windInfo;
};
