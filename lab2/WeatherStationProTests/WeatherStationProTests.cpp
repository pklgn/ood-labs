#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationPro/WeatherData/Displays/Display.h"
#include "../WeatherStationPro/WeatherData/Displays/StatisticsDisplay.h"
#include "../WeatherStationPro/WeatherData/WeatherData.h"
#include "TestStatisticsDisplay.h"

TEST_CASE("observer remove itself from the set of observers")
{
	WeatherData wd;
	std::ostringstream output;

	Display display(output);
	wd.RegisterObserver(display);

	SWeatherInfo weatherInfo{ 3, 0.8, 761, 4, 90 };
	wd.SetMeasurements(weatherInfo);
	REQUIRE(output.str() == "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\nCurrent Wind Speed: 4\nCurrent Wind Angle: 90\n------------------\n");
}

TEST_CASE("several observers remove themselves from the set of observers")
{
	WeatherData wd;
	std::ostringstream output;

	Display display1(output);
	wd.RegisterObserver(display1);

	Display display2(output);
	wd.RegisterObserver(display2);

	SWeatherInfo weatherInfo{ 3, 0.8, 761, 4, 90 };

	std::stringstream expextedOutput("Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\nCurrent Wind Speed: 4\nCurrent Wind Angle: 90\n------------------\n"
									 "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\nCurrent Wind Speed: 4\nCurrent Wind Angle: 90\n------------------\n");

	wd.SetMeasurements(weatherInfo);
	REQUIRE(output.str() == expextedOutput.str());
}

TEST_CASE("check negative angle input")
{
	WeatherData wd;
	std::ostringstream output;

	Display display(output);
	wd.RegisterObserver(display);

	SWeatherInfo weatherInfo{ 3, 0.8, 761, 4, -90 };
	wd.SetMeasurements(weatherInfo);
	REQUIRE(output.str() == "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\nCurrent Wind Speed: 4\nCurrent Wind Angle: 270\n------------------\n");
}

TEST_CASE("check over full angle input")
{
	WeatherData wd;
	std::ostringstream output;

	Display display(output);
	wd.RegisterObserver(display);

	SWeatherInfo weatherInfo{ 3, 0.8, 761, 4, 370 };
	wd.SetMeasurements(weatherInfo);
	REQUIRE(output.str() == "Current Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\nCurrent Wind Speed: 4\nCurrent Wind Angle: 10\n------------------\n");
}

TEST_CASE("check sequence of angles")
{
	WeatherData wd;
	std::ostringstream output;

	TestStatisticsDisplay display(output);
	wd.RegisterObserver(display);

	SWeatherInfo weatherInfo{ 3, 0.8, 761, 4, 90 };
	wd.SetMeasurements(weatherInfo);
	weatherInfo = { 3, 0.8, 761, 4, 180 };
	wd.SetMeasurements(weatherInfo);
	weatherInfo = { 3, 0.8, 761, 4, 270 };
	wd.SetMeasurements(weatherInfo);
	output.str("");

	weatherInfo = { 3, 0.8, 761, 4, 360 };
	wd.SetMeasurements(weatherInfo);
	std::stringstream expextedOutput("WIND ANGLE:\nMax 270.00\nMin 0.00\nAvg 270.00\n----------------\n");
	REQUIRE(output.str() == expextedOutput.str());
}

TEST_CASE("check simple sequence of angles")
{
	WeatherData wd;
	std::ostringstream output;

	TestStatisticsDisplay display(output);
	wd.RegisterObserver(display);

	SWeatherInfo weatherInfo{ 3, 0.8, 761, 4, 10 };
	wd.SetMeasurements(weatherInfo);
	weatherInfo = { 3, 0.8, 761, 4, 20 };
	wd.SetMeasurements(weatherInfo);
	output.str("");

	weatherInfo = { 3, 0.8, 761, 4, 30 };
	wd.SetMeasurements(weatherInfo);
	std::stringstream expextedOutput("WIND ANGLE:\nMax 30.00\nMin 10.00\nAvg 20.00\n----------------\n");
	REQUIRE(output.str() == expextedOutput.str());
}
