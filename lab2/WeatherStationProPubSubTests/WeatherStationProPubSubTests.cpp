#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationProPubSub/WeatherData/Display/Display.h"
#include "../WeatherStationProPubSub/WeatherData/Display/StatisticsDisplay.h"
#include "../WeatherStationProPubSub/WeatherData/WeatherData.h"
#include "../WeatherStationProPubSub/Dependents/Dependents.hpp"
#include "../WeatherStationProPubSub/WeatherData/Handlers/Handlers.h"
#include "../WeatherStationProPubSub/WeatherData/Handlers/StatisticsHandlers.h"

TEST_CASE("simple test")
{
	WeatherData weatherData;

	Display display(std::cout);

	//Check basic case with one handler
	weatherData.AddObserver(&display, WeatherEvent::TEMPRATURE, [&]() {
		OnTempratureChange(weatherData);
		OnTempratureStatisticsChange(weatherData);
	});
	SWeatherInfo weatherInfo = { 34, 0.8, 760, 2, 90 };
	weatherData.SetMeasurements(weatherInfo);

	weatherInfo = { 35, 0.9, 761, 3, 91 };
	weatherData.SetMeasurements(weatherInfo);

	weatherData.RemoveObserver(&display, WeatherEvent::TEMPRATURE);

	//Check after temprature removing and adding wind_angle observer
	weatherInfo = { 36, 1, 762, 4, 92 };
	weatherData.AddObserver(&display, WeatherEvent::WIND_ANGLE, [&]() {
		OnWindAngleChange(weatherData);
		OnWindAngleStatisticsChange(weatherData);
	});
	weatherData.SetMeasurements(weatherInfo);
}