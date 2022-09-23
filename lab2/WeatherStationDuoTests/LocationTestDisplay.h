#pragma once

#include "../WeatherStationDuo/WeatherData/Displays/Display.h"

class LocationTestDisplay : public Display
{
public:
	LocationTestDisplay(std::ostream&);

	void Update(SWeatherInfo const& data) override;
};