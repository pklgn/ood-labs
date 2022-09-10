#include <iostream>
#include "Duck.h"

void Duck::PerformFly()
{
	if (m_flyBehavior->Fly())
	{
		std::cout << "Flight #" << ++m_flightsCount << " was performed\n";
	}
}

void Duck::PerformQuack() const
{
	m_quackBehavior->Quack();
}

void Duck::PerformDance() const
{
	m_danceBehavior->Dance();
}

count_type Duck::GetFlightsCount() const
{
	return m_flightsCount;
}

void Duck::Swim()
{
	std::cout << "Swimming!\n";
}

void Duck::SetFlyBehavior(IFlyBehavior* behavior)
{
	m_flyBehavior.reset(behavior);
}

void Duck::SetQuackBehavior(IQuackBehavior* behavior)
{
	m_quackBehavior.reset(behavior);
}

void Duck::SetDanceBehavior(IDanceBehavior* behavior)
{
	m_danceBehavior.reset(behavior);
}