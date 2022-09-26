#pragma once

#include "../WeatherStationDuoMeta/WeatherData/Displays/Display.h"

class LocationTestDisplay : public Display
{
public:
	LocationTestDisplay(std::ostream&);

	void Update(SWeatherInfo const& data, Location const& location) override;
};