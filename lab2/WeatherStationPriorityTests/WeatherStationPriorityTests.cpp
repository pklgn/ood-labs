#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationPriority/WeatherData/WeatherData.h"
#include "../WeatherStationPriority/WeatherData/Displays/Display.h"
#include "../WeatherStationPriority/WeatherData/Displays/StatisticsDisplay.h"

TEST_CASE("Add one priority level")
{
	WeatherData wd;
	std::ostringstream output;

	Display display1(output);
	unsigned int priority = 1;
	wd.RegisterObserver(display1, priority);
	wd.SetMeasurements(3, 0.8, 761);
	REQUIRE(output.str() == "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n");
	output.str("");

	wd.SetMeasurements(10, 0.9, 758);
	REQUIRE(output.str() == "Current Temprature: 10\nCurrent Humidity: 0.9\nCurrent Pressure: 758\n------------------\n");
	output.str("");

	StatisticsDisplay statisticsDisplay(output);
	wd.RegisterObserver(statisticsDisplay, priority);

	wd.SetMeasurements(3, 0.8, 761);

	std::stringstream expectedOutput("Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n"
									 "TEMPRATURE:\nMax 3.00\nMin 3.00\nAvg 3.00\n----------------\n"
									 "HUMIDITY:\nMax 0.80\nMin 0.80\nAvg 0.80\n----------------\n"
									 "PRESSURE:\nMax 761.00\nMin 761.00\nAvg 761.00\n----------------\n");
	REQUIRE(output.str() == expectedOutput.str());
	output.str("");
}

TEST_CASE("Add different priorities")
{
	WeatherData wd;
	std::ostringstream output;

	Display display1(output);
	unsigned int priority = 1;

	wd.RegisterObserver(display1, priority);

	StatisticsDisplay statisticsDisplay(output);
	wd.RegisterObserver(statisticsDisplay, priority - 1);

	wd.SetMeasurements(3, 0.8, 761);

	std::stringstream expectedOutput("TEMPRATURE:\nMax 3.00\nMin 3.00\nAvg 3.00\n----------------\n"
									 "HUMIDITY:\nMax 0.80\nMin 0.80\nAvg 0.80\n----------------\n"
									 "PRESSURE:\nMax 761.00\nMin 761.00\nAvg 761.00\n----------------\n"
									 "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n");
	REQUIRE(output.str() == expectedOutput.str());
	output.str("");

	wd.RemoveObserver(statisticsDisplay);
	wd.SetMeasurements(5, 2, 762);
	expectedOutput.str("Current Temprature: 5\nCurrent Humidity: 2\nCurrent Pressure: 762\n------------------\n");
	REQUIRE(output.str() == expectedOutput.str());
	output.str("");

	wd.RemoveObserver(display1);

	wd.SetMeasurements(5, 2, 762);
	REQUIRE(output.str() == "");
}