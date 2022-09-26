#pragma once

#include "../WeatherStationProDuo/WeatherData/Displays/Display.h"

class LocationTestDisplay : public Display
{
public:
	LocationTestDisplay(std::ostream& output);

	void Update(SWeatherInfo const& data) override;
};