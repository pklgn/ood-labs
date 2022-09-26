#pragma once

#include "Dependents.hpp"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

enum class Location
{
	INSIDE,
	OUTSIDE,
	UNKNOWN,
};

class WeatherObserver : public IObserver<SWeatherInfo>
{
protected:
	IObservable<SWeatherInfo>* m_weatherInside;
	IObservable<SWeatherInfo>* m_weatherOutside;
};

class WeatherObservable : public IObservable<SWeatherInfo>
{
	using ObserverType = WeatherObserver;
	using ObserverPriorityType = unsigned short;

};