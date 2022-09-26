#pragma once

#include <optional>
#include "../pch.h"
#include "../Dependents/Dependents.hpp"

struct SWindInfo
{
	double speed = 0;
	double angle = 0;
};

struct SWeatherInfo
{
	std::optional<double> temperature = std::nullopt;
	std::optional<double> humidity = std::nullopt;
	std::optional<double> pressure = std::nullopt;
	std::optional<SWindInfo> wind = std::nullopt;
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

	void MeasurementsChanged(SWeatherInfo&);

	void SetMeasurements(SWeatherInfo&);

protected:
	SWeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_windInfo;
};
