#include "../../pch.h"
#include "Display.h"

void Display::Update(SWeatherInfo const& data)
{
	std::cout << "Current Temprature:\t" << data.temperature << std::endl;
	std::cout << "Current Humidity:\t" << data.humidity << std::endl;
	std::cout << "Current Pressure:\t" << data.pressure << std::endl;
	std::cout << "-----------------" << std::endl;
}