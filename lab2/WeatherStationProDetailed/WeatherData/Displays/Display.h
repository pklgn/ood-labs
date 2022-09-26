#pragma once

#include "../WeatherData.h"

class Display : public Subscriber
{
public:
	Display(std::ostream&);

protected:
	std::ostream& m_output;

	/* Метод Update сделан защищенным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(double newValue, WeatherEvent) override;
};
