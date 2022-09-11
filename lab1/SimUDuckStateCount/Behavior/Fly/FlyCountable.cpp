#include <iostream>
#include "FlyCountable.h"

FlyCountable::count_type FlyCountable::GetFlightsCount()
{
	return m_flightsCount;
}

void FlyCountable::PrintFlightsCount()
{
	std::cout <<  "Flight #" << m_flightsCount << " was performed\n";
}