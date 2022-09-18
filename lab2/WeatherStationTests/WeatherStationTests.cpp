#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStation/WeatherData/WeatherData.h"
#include "../WeatherStation/WeatherData/Displays/Display.h"
#include "../WeatherStation/WeatherData/Displays/StatisticsDisplay.h"

TEST_CASE("observer remove itself from the set of observers")
{
	WeatherData wd;
	std::ostringstream output;

	Display display(output);
	wd.RegisterObserver(display);
	wd.SetMeasurements(3, 0.8, 761);
	REQUIRE_NOTHROW(wd.SetMeasurements(3, 0.8, 761));
	REQUIRE(output.str() == "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n");
}

TEST_CASE("several observers remove themselves from the set of observers")
{
	WeatherData wd;
	std::ostringstream output;

	Display display1(output);
	wd.RegisterObserver(display1);

	Display display2(output);
	wd.RegisterObserver(display2);

	wd.SetMeasurements(3, 0.8, 761);

	std::stringstream expextedOutput("Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n"
									 "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n");
	REQUIRE(output.str() == expextedOutput.str());
	output.str("");

	wd.SetMeasurements(4, 0.9, 762);
	REQUIRE(output.str() == "");
}
