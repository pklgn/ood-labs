#include <iostream>
#include "FlyWithWings.h"

void FlyWithWings::Fly()
{
	std::cout << "Flying with wings!\n";
	CountFlight();
	PrintFlightsCount();
}

void FlyWithWings::CountFlight()
{
	++m_flightsCount;
}

// TODO: сделать подсчет в каждом поведении независимо 