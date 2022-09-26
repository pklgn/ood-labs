#pragma once

#include "../pch.h"
#include "../Dependents/Dependents.hpp"

enum class Version
{
	BASIC,
	PRO,
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
	Version version = Version::BASIC;
};

class WeatherData : public Observable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const;

	// Относительная влажность (0...100)
	double GetHumidity() const;

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const;

	void MeasurementsChanged();

	virtual void SetMeasurements(SWeatherInfo&);

protected:
	SWeatherInfo GetChangedData() const override;

	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class WeatherDataPro : public WeatherData
{
public:
	SWindInfo GetWindInfo() const;

	void SetMeasurements(SWeatherInfo&) override;

protected:
	SWeatherInfo GetChangedData() const override;

private:
	SWindInfo m_windInfo;
};
