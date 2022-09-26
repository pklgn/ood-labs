#pragma once

#include "../WeatherStationPro/WeatherData/Displays/StatisticsDisplay.h"

class TestStatisticsDisplay : public StatisticsDisplay
{
public:
	TestStatisticsDisplay(std::ostream&);

	void Update(SWeatherInfo const& data) override;
};