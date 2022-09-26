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

	std::stringstream prospectiveOutput("21");
	REQUIRE(output.str() == prospectiveOutput.str());
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

	std::stringstream prospectiveOutput("INSIDE");
	REQUIRE(prospectiveOutput.str() == output.str());
	output.str("");

	oWD.SetMeasurements(3, 0.8, 761);
	prospectiveOutput.str("OUTSIDE");
	REQUIRE(prospectiveOutput.str() == output.str());
}