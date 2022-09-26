#pragma once

#include "../WeatherData.h"
#include "StatisticsDisplayComponent.h"
#include "StatisticsDisplayAngleComponent.h"

class StatisticsDisplay : public Subscriber
{
public:
	StatisticsDisplay(std::ostream&);

protected:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(double newValue, WeatherEvent) override;

	StatisticsDisplayComponent m_temprature;
	StatisticsDisplayComponent m_humidity;
	StatisticsDisplayComponent m_pressure;
	StatisticsDisplayComponent m_windSpeed;
	StatisticsDisplayAngleComponent m_windAngle;

};