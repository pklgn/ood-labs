#include <iostream>
#include "QuackStrategies.h"

std::function<void()> GetCommonQuackFunction()
{
	return [&]() {
		std::cout << "Quacking!\n";
	};
}

std::function<void()> GetMuteQuackFunction()
{
	return [&]() {
		std::cout << "Mute quacking!\n";
	};
}

std::function<void()> GetSqueakFunction()
{
	return []() {
		std::cout << "Squeaking!\n";
	};
}