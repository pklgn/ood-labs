#pragma once

#include "../WeatherStationDuoPtr/WeatherData/Displays/Display.h"

class LocationTestDisplay : public Display
{
public:
	LocationTestDisplay(std::ostream& output, ObservablePtrType weatherInside, ObservablePtrType weatherOutside);

	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const&) override;
};