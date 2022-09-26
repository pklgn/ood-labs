#pragma once

#include "../WeatherData.h"

class Display : public IObserver<SWeatherInfo, Location>
{
public:
	Display(std::ostream&);

protected:
	std::ostream& m_output;

	/* Метод Update сделан защищенным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, Location const& metaData) override;
};
