#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationProDuo/WeatherData/Displays/Display.h"
#include "../WeatherStationProDuo/WeatherData/Displays/StatisticsDisplay.h"
#include "../WeatherStationProDuo/WeatherData/WeatherData.h"
#include "LocationTestDisplay.h"

TEST_CASE("Check correct displaying of the WD location by SetMeasurements update")
{
	WeatherData iWD;
	WeatherDataPro oWD;

	std::ostringstream output;
	LocationTestDisplay locationDisplay(output);
	iWD.RegisterObserver(locationDisplay);
	oWD.RegisterObserver(locationDisplay);

	SWeatherInfo weatherInfo = { 3, 0.8, 761 };
	iWD.SetMeasurements(weatherInfo);

	std::stringstream expectedOutput("INSIDE");
	REQUIRE(expectedOutput.str() == output.str());

	output.str("");
	SWeatherInfo weatherInfoPro = { 3, 0.8, 761, 4, 90 };
	oWD.SetMeasurements(weatherInfoPro);
	expectedOutput.str("OUTSIDE");
	REQUIRE(expectedOutput.str() == output.str());
}