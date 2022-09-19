#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherDataFull/WeatherData/WeatherData.h"
#include "../WeatherDataFull/WeatherData/Displays/Display.h"
#include "../WeatherDataFull/WeatherData/Displays/StatisticsDisplay.h"

TEST_CASE("Check display update")
{
	WeatherData wd;
	std::ostringstream output;

	Display display(output);
	wd.RegisterObserver(display);
	wd.SetMeasurements(3, 0.8, 761);
	REQUIRE(output.str() == "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n");
	output.str("");
	
	wd.SetMeasurements(10, 0.9, 758);
	REQUIRE(output.str() == "Current Temprature: 10\nCurrent Humidity: 0.9\nCurrent Pressure: 758\n------------------\n");
}

TEST_CASE("Check statistics display update")
{
	WeatherData wd;
	std::ostringstream output;

	StatisticsDisplay statisticsDisplay(output);
	wd.RegisterObserver(statisticsDisplay);
	wd.SetMeasurements(3, 0.8, 761);

	std::stringstream expextedOutput("TEMPRATURE:\nMax 3.00\nMin 3.00\nAvg 3.00\n----------------\n"
									 "HUMIDITY:\nMax 0.80\nMin 0.80\nAvg 0.80\n----------------\n"
									 "PRESSURE:\nMax 761.00\nMin 761.00\nAvg 761.00\n----------------\n");
	REQUIRE(output.str() == expextedOutput.str());
	output.str("");

	wd.SetMeasurements(4, 0.9, 762);
	expextedOutput.str("TEMPRATURE:\nMax 4.00\nMin 3.00\nAvg 3.50\n----------------\n"
					   "HUMIDITY:\nMax 0.90\nMin 0.80\nAvg 0.85\n----------------\n"
					   "PRESSURE:\nMax 762.00\nMin 761.00\nAvg 761.50\n----------------\n");
	REQUIRE(output.str() == expextedOutput.str());
}

TEST_CASE("Check display and statistics display update simultaneously")
{
	WeatherData wd;
	std::ostringstream output;

	Display display(output);
	wd.RegisterObserver(display);

	StatisticsDisplay statisticsDisplay(output);
	wd.RegisterObserver(statisticsDisplay);

	wd.SetMeasurements(3, 0.8, 761);

	std::stringstream expextedOutput("Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n"
									 "TEMPRATURE:\nMax 3.00\nMin 3.00\nAvg 3.00\n----------------\n"
									 "HUMIDITY:\nMax 0.80\nMin 0.80\nAvg 0.80\n----------------\n"
									 "PRESSURE:\nMax 761.00\nMin 761.00\nAvg 761.00\n----------------\n");
	REQUIRE(output.str() == expextedOutput.str());
	output.str("");

	wd.SetMeasurements(4, 0.9, 762);
	expextedOutput.str("Current Temprature: 4\nCurrent Humidity: 0.9\nCurrent Pressure: 762\n------------------\n"
					   "TEMPRATURE:\nMax 4.00\nMin 3.00\nAvg 3.50\n----------------\n"
					   "HUMIDITY:\nMax 0.90\nMin 0.80\nAvg 0.85\n----------------\n"
					   "PRESSURE:\nMax 762.00\nMin 761.00\nAvg 761.50\n----------------\n");
	REQUIRE(output.str() == expextedOutput.str());
	output.str("");

	wd.RemoveObserver(statisticsDisplay);
	wd.SetMeasurements(5, 1, 763);
	REQUIRE(output.str() == "Current Temprature: 5\nCurrent Humidity: 1\nCurrent Pressure: 763\n------------------\n");
	output.str("");
}

TEST_CASE("Check desctructor")
{
	WeatherData wd;
	std::ostringstream output;

	{
		Display display(output);
		wd.RegisterObserver(display);
		wd.SetMeasurements(3, 0.8, 761);
		std::stringstream expextedOutput("Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n");
		REQUIRE(output.str() == expextedOutput.str());
		output.str("");
	}

	wd.SetMeasurements(3, 0.8, 761);
	REQUIRE_NOTHROW(wd.SetMeasurements(3, 0.8, 761));
}