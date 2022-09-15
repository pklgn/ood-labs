#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "../Dependents/Dependents.hpp"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class StatisticsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		if (m_minTemperature > data.temperature)
		{
			m_minTemperature = data.temperature;
		}
		if (m_maxTemperature < data.temperature)
		{
			m_maxTemperature = data.temperature;
		}
		m_accTemperature += data.temperature;
		++m_countAcc;

		std::cout << "Max Temp " << m_maxTemperature << std::endl;
		std::cout << "Min Temp " << m_minTemperature << std::endl;
		std::cout << "Average Temp " << (m_accTemperature / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	double m_minTemperature = std::numeric_limits<double>::infinity();
	double m_maxTemperature = -std::numeric_limits<double>::infinity();
	double m_accTemperature = 0;
	unsigned m_countAcc = 0;
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

	void SetMeasurements(double temp, double humidity, double pressure);

protected:
	SWeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
