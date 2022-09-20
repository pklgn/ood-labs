#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationDuo/WeatherData/Displays/Display.h"
#include "../WeatherStationDuo/WeatherData/Displays/StatisticsDisplay.h"

TEST_CASE("simple test")
{
	WeatherData wd(Location::INDOORS);

	{
		wd.RegisterObserver(std::make_shared<Display>(Display(std::cout)), 10);
		wd.NotifyObservers();
	}
	wd.NotifyObservers();
}

class TestingObserver : public IObserver<SWeatherInfo>
{
private:
	void Update(const SWeatherInfo& info, IObservable<SWeatherInfo>& observable)
	{
		observable.RemoveObserver(std::make_shared<TestingObserver>(*this));
	}
};

TEST_CASE("simple test 2")
{
	WeatherData wd(Location::INDOORS);

	wd.RegisterObserver(std::make_shared<TestingObserver>(TestingObserver()), 10);

	wd.SetMeasurements(3, 0.8, 761);
	wd.SetMeasurements(3, 0.8, 761);
}
