#pragma once

#include "../WeatherStationDuo/WeatherData/Displays/Display.h"

class MockDisplay : public Display
{
public:
	MockDisplay(std::ostream&, const std::string& mockInfo);

	void Update(SWeatherInfo const& data) override;

private:
	std::string m_mockInfo;
};
