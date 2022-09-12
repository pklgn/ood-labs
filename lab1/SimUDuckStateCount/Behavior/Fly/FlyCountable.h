#pragma once
#include "IFlyBehavior.h"

class FlyCountable : public IFlyBehavior
{
public:
	using count_type = size_t;

	count_type GetFlightsCount();

protected:
	count_type m_flightsCount = 0;

	virtual void CountFlight() = 0;
	void PrintFlightsCount();
};