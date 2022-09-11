#include <iostream>
#include "FlyStrategies.h"

std::function<void()> GetFlyWithWingsFunction(){
	count_type flightsCount = 0;

	return [&]() {
		std::cout << "Flying with wings!\n";
		++flightsCount;
		std::cout << "Flight #" << flightsCount << " was performed!\n";
	};
}

std::function<void()> GetFlyWithRocketPowerFunction()
{
	count_type flightsCount = 0;

	return [&]() {
		std::cout << "Flying with rocket power!\n";
		++flightsCount;
		std::cout << "Flight #" << flightsCount << " was performed!\n";
	};
}

std::function<void()> GetFlyNoWayFunction()
{
	return []() {
		std::cout << "Flying no way!\n";
	};
}