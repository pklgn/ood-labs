#pragma once

#include "../pch.h"
#include "../Dependents/Dependents.hpp"

enum class Location
{
	INSIDE,
	OUTSIDE,
	UNKNOWN,
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class WeatherData : public Observable<SWeatherInfo, Location>
{
public:
	WeatherData(Location location = Location::UNKNOWN);

	// Температура в градусах Цельсия
	double GetTemperature() const;

	// Относительная влажность (0...100)
	double GetHumidity() const;

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const;

	Location GetLocation() const;

	void MeasurementsChanged();

	void SetMeasurements(double temp, double humidity, double pressure);

protected:
	SWeatherInfo GetChangedData() const override;

	Location GetMetaData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	Location m_location = Location::UNKNOWN;
};
