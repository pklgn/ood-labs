#pragma once
#include "../../pch.h"
#include "../WeatherData.h"

std::function<void(WeatherData&)> OnTempratureChange = [](WeatherData& wd) {
	std::cout << "Temprature: " << wd.GetTemperature() << std::endl;
};

std::function<void(WeatherData&)> OnHumidityChange = [](WeatherData& wd) {
	std::cout << "Humidity: " << wd.GetHumidity() << std::endl;
};

std::function<void(WeatherData&)> OnPressureChange = [](WeatherData& wd) {
	std::cout << "Pressure: " << wd.GetPressure() << std::endl;
};

std::function<void(WeatherData&)> OnWindSpeedChange = [](WeatherData& wd) {
	std::cout << "Wind speed: " << wd.GetWindInfo().speed << std::endl;
};

std::function<void(WeatherData&)> OnWindAngleChange = [](WeatherData& wd) {
	std::cout << "Wind angle: " << wd.GetWindInfo().angle << std::endl;
};
