#include <iostream>
#include "DanceStrategies.h"

std::function<void()> GetDanceWaltzFunction()
{
	return []() {
		std::cout << "Dancing waltz!\n";
	};
}

std::function<void()> GetDanceNoWayFunction()
{
	return []() {
		std::cout << "Dancing no way!\n";
	};
}

std::function<void()> GetDanceMinuetFunction()
{
	return []() {
		std::cout << "Dancing minuet!\n";
	};
}