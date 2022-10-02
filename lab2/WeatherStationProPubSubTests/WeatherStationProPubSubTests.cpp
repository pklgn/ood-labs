#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationProPubSub/WeatherData/Display/Display.h"
#include "../WeatherStationProPubSub/WeatherData/Display/StatisticsDisplay.h"
#include "../WeatherStationProPubSub/WeatherData/WeatherData.h"
#include "../WeatherStationProPubSub/Dependents/Dependents.hpp"

TEST_CASE("simple test")
{
	Broker<WeatherEvent> broker;
	WeatherData publisher;
	broker.RegisterToPublisher(&publisher);

	Display display(std::cout);
	std::function<void()> handler = [&]() {
		std::cout << publisher.GetTemperature() << std::endl;
		
		std::cout << "hello\n";
	};
	broker.AddSubscriber(&display, WeatherEvent::TEMPRATURE, handler);

	SWeatherInfo weatherInfo = { 34, 0.8, 760, 2, 90 };

	publisher.SetMeasurements(weatherInfo);

	weatherInfo = { 35, 0.9, 761, 3, 91 };
	publisher.SetMeasurements(weatherInfo);

	//display.SubscribeToBroker(&broker, WeatherEvent::HUMIDITY, handler);
	//publisher.SetMeasurements(weatherInfo);
}