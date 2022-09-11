#include <iostream>
#include "FlyWithRocketPower.h"

void FlyWithRocketPower::Fly()
{
	std::cout << "Flying with rocket power!\n";
	CountFlight();
	PrintFlightsCount();
}

void FlyWithRocketPower::CountFlight()
{
	++m_flightsCount;
}