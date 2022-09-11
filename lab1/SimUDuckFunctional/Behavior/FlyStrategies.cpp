#include <iostream>
#include "FlyStrategies.h"

std::function<bool()> GetFlyWithWingsFunction(){
	return []() {
		std::cout << "Flying with wings!\n";

		return true;
	};
}

std::function<bool()> GetFlyWithRocketPowerFunction()
{
	return []() {
		std::cout << "Flying with rocket power!\n";

		return true;
	};
}

std::function<bool()> GetFlyNoWayFunction()
{
	return []() {
		std::cout << "Flying no way!\n";

		return false;
	};
}