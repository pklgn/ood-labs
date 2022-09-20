#pragma once

#include "../WeatherData.h"

class Display : public IObserver<SWeatherInfo>
{
public:
	Display(std::ostream&);

private:
	std::ostream& m_output;
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override;
};
