#pragma once

#include "../WeatherData.h"
#include "StatisticsDisplayComponent.h"

class StatisticsDisplay : public Observer<SWeatherInfo>
{
public:
	StatisticsDisplay(std::ostream&);

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override;

	StatisticsDisplayComponent m_temprature;
	StatisticsDisplayComponent m_humidity;
	StatisticsDisplayComponent m_pressure;
};