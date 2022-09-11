#pragma once
#include "IFlyBehavior.h"

class FlyCountable : public IFlyBehavior
{
public:
	using count_type = size_t;

	count_type GetFlightsCount();

protected:
	virtual void CountFlight() = 0;
	void PrintFlightsCount();
	count_type m_flightsCount = 0;
};