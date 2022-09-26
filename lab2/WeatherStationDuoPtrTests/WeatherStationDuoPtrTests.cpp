#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationDuoPtr/WeatherData/WeatherData.h"
#include "LocationTestDisplay.h"
#include "../WeatherStationDuoPtr/WeatherData/Displays/StatisticsDisplay.h"

TEST_CASE("Check correct displaying of the WD location by SetMeasurements update")
{
	WeatherData iWD;
	WeatherData oWD;

	std::ostringstream output;
	LocationTestDisplay locationDisplay(output, &iWD, &oWD);
	iWD.RegisterObserver(locationDisplay);
	oWD.RegisterObserver(locationDisplay);

	iWD.SetMeasurements(3, 0.8, 761);

	std::stringstream prospectiveOutput("INSIDE");
	REQUIRE(prospectiveOutput.str() == output.str());

	output.str("");
	oWD.SetMeasurements(1, 1, 777);
	prospectiveOutput.str("OUTSIDE");
	REQUIRE(prospectiveOutput.str() == output.str());
}

TEST_CASE("Check common Display output")
{
	WeatherData iWD;
	WeatherData oWD;

	std::ostringstream output;
	Display display(output, &iWD, &oWD);
	iWD.RegisterObserver(display);
	oWD.RegisterObserver(display);

	iWD.SetMeasurements(3, 0.8, 761);
	std::stringstream prospectiveOutput("Location: INSIDE\nCurrent Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n");
	REQUIRE(prospectiveOutput.str() == output.str());
	output.str("");

	oWD.SetMeasurements(3, 0.8, 761);
	prospectiveOutput.str("Location: OUTSIDE\nCurrent Temprature: 3\nCurrent Humidity: 0.8\nCurrent Pressure: 761\n------------------\n");
	REQUIRE(prospectiveOutput.str() == output.str());
}

TEST_CASE("Check Statistics Display output")
{
	WeatherData iWD;
	WeatherData oWD;

	std::ostringstream output;
	StatisticsDisplay display(output, &iWD, &oWD);
	iWD.RegisterObserver(display);
	oWD.RegisterObserver(display);

	iWD.SetMeasurements(3, 0.8, 761);
	std::stringstream prospectiveOutput("Location: INSIDE\n"
										"TEMPRATURE:\nMax 3.00\nMin 3.00\nAvg 3.00\n----------------\n"
										"HUMIDITY:\nMax 0.80\nMin 0.80\nAvg 0.80\n----------------\n"
										"PRESSURE:\nMax 761.00\nMin 761.00\nAvg 761.00\n----------------\n");
	REQUIRE(prospectiveOutput.str() == output.str());
	output.str("");

	oWD.SetMeasurements(3, 0.8, 761);
	prospectiveOutput.str("Location: OUTSIDE\n"
						  "TEMPRATURE:\nMax 3.00\nMin 3.00\nAvg 3.00\n----------------\n"
						  "HUMIDITY:\nMax 0.80\nMin 0.80\nAvg 0.80\n----------------\n"
						  "PRESSURE:\nMax 761.00\nMin 761.00\nAvg 761.00\n----------------\n");
	REQUIRE(prospectiveOutput.str() == output.str());
}