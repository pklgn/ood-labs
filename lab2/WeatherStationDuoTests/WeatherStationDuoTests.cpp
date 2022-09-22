#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationDuo/WeatherData/WeatherData.h"
#include "MockDisplay.h"
#include "LocationTestDisplay.h"

TEST_CASE("Check priority")
{
	WeatherData wd(Location::INSIDE);
	std::ostringstream output;

	MockDisplay mockDisplay1(output, "1");
	unsigned short priority = 1;
	wd.RegisterObserver(mockDisplay1, priority);

	MockDisplay mockDisplay2(output, "2");
	wd.RegisterObserver(mockDisplay2, priority - 1);

	wd.SetMeasurements(3, 0.8, 761);

	std::stringstream expectedOutput("21");
	REQUIRE(output.str() == expectedOutput.str());
	output.str("");
}

TEST_CASE("Check correct displaying of the WD location by SetMeasurements update")
{
	WeatherData iWD(Location::INSIDE);
	WeatherData oWD(Location::OUTSIDE);

	std::ostringstream output;
	LocationTestDisplay locationDisplay(output);
	iWD.RegisterObserver(locationDisplay);
	oWD.RegisterObserver(locationDisplay);

	iWD.SetMeasurements(3, 0.8, 761);

	std::stringstream expectedOutput("INSIDE");
	REQUIRE(expectedOutput.str() == output.str());
}