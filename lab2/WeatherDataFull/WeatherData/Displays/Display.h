#pragma once

#include "../WeatherData.h"
#include "../../Dependents/Dependents.hpp"


class Display : public IObserver<SWeatherInfo>

{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу Observable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override;
};