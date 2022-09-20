﻿#pragma once

#include "../pch.h"
#include "../Dependents/Dependents.hpp"

enum class Location
{
	INDOORS,
	OUTDOORS,
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	Location location = Location::INDOORS;
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

	void MeasurementsChanged();

	void SetMeasurements(double temp, double humidity, double pressure);

protected:
	SWeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
	Location m_location = Location::INDOORS;
};
