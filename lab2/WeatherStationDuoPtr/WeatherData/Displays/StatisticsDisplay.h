#pragma once

#include "../WeatherData.h"
#include "Display.h"
#include "StatisticsDisplayComponent.h"

class StatisticsDisplay : public Display
{
public:
	StatisticsDisplay(std::ostream&, ObservablePtrType, ObservablePtrType);

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override;

	StatisticsDisplayComponent m_temprature;
	StatisticsDisplayComponent m_humidity;
	StatisticsDisplayComponent m_pressure;
};