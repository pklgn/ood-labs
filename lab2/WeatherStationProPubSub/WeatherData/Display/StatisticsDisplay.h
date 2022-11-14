#pragma once

#include "../WeatherData.h"
#include "StatisticsDisplayComponent.h"
#include "StatisticsDisplayAngleComponent.h"

class StatisticsDisplay : public IObservable<WeatherEvent>
{
public:
	StatisticsDisplay(std::ostream&);

protected:

	StatisticsDisplayComponent m_temprature;
};