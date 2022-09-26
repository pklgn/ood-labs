#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationProDetailed/Dependents/Dependents.hpp"
#include "../WeatherStationProDetailed/WeatherData/WeatherData.h"
#include "../WeatherStationProDetailed/WeatherData/Displays/Display.h"
#include "../WeatherStationProDetailed/WeatherData/Displays/StatisticsDisplay.h"

TEST_CASE("Check correct subsribing")
{
	Broker broker;
	WeatherData publisher;
	broker.RegisterToPublisher(&publisher);

	Display display(std::cout);
	display.SubscribeToBroker(&broker, WeatherEvent::TEMPRATURE);

	SWeatherInfo weatherInfo = { 100 };

	publisher.SetMeasurements(weatherInfo);

	weatherInfo = { std::nullopt, 0.8 };
	publisher.SetMeasurements(weatherInfo);

	display.SubscribeToBroker(&broker, WeatherEvent::HUMIDITY);
	publisher.SetMeasurements(weatherInfo);
}