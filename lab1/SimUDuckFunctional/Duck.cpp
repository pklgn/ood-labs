#include <iostream>
#include "Duck.h"

void Duck::PerformFly()
{
	if (m_flyBehavior())
	{
		std::cout << "Flight #" << ++m_flightsCount << " was performed\n";
	}
}

void Duck::PerformQuack() const
{
	m_quackBehavior();
}

void Duck::PerformDance() const
{
	m_danceBehavior();
}

size_t Duck::GetFlightsCount() const
{
	return m_flightsCount;
}

void Duck::Swim()
{
	std::cout << "Swimming!\n";
}

void Duck::SetFlyBehavior(std::function<bool()>& behavior)
{
	m_flyBehavior = std::move(behavior);
}

void Duck::SetQuackBehavior(std::function<void()>& behavior)
{
	m_quackBehavior = std::move(behavior);
}

void Duck::SetDanceBehavior(std::function<void()>& behavior)
{
	m_danceBehavior = std::move(behavior);
}