#pragma once

#include "../WeatherData.h"
#include "StatisticsDisplayComponent.h"

class StatisticsDisplay : public IObserver<SWeatherInfo, Location>
{
public:
	StatisticsDisplay(std::ostream&);

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, Location const& metaData) override;

	StatisticsDisplayComponent m_temprature;
	StatisticsDisplayComponent m_humidity;
	StatisticsDisplayComponent m_pressure;
};