#pragma once
#include "../../pch.h"
#include "../WeatherData.h"
#include "../Display/StatisticsDisplayComponent.h"
#include "../Display/StatisticsDisplayAngleComponent.h"

std::function<void(WeatherData wd)> OnTempratureStatisticsChange =
	[temprature = StatisticsDisplayComponent(ComponentType::TEMPRATURE, std::cout)](WeatherData wd) mutable {
		temprature.UpdateData(wd.GetTemperature());
		temprature.PrintData();
	};

std::function<void(WeatherData wd)> OnHumidityStatisticsChange =
	[humidity = StatisticsDisplayComponent(ComponentType::HUMIDITY, std::cout)](WeatherData wd) mutable {
		humidity.UpdateData(wd.GetHumidity());
		humidity.PrintData();
	};

std::function<void(WeatherData wd)> OnPressureStatisticsChange =
	[pressure = StatisticsDisplayComponent(ComponentType::PRESSURE, std::cout)](WeatherData wd) mutable {
		pressure.UpdateData(wd.GetPressure());
		pressure.PrintData();
	};

std::function<void(WeatherData wd)> OnWindSpeedStatisticsChange =
	[windSpeed = StatisticsDisplayComponent(ComponentType::WIND_SPEED, std::cout)](WeatherData wd) mutable {
		windSpeed.UpdateData(wd.GetWindInfo().speed);
		windSpeed.PrintData();
	};

std::function<void(WeatherData wd)> OnWindAngleStatisticsChange =
	[windAngle = StatisticsDisplayAngleComponent(ComponentType::WIND_ANGLE, std::cout)](WeatherData wd) mutable {
		windAngle.UpdateData(wd.GetWindInfo().angle);
		windAngle.PrintData();
	};