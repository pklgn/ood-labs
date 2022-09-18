#include <iostream>
#include "Duck.h"

void Duck::PerformFly()
{
	m_flyBehavior->Fly();
}

void Duck::PerformQuack() const
{
	m_quackBehavior->Quack();
}

void Duck::PerformDance() const
{
	m_danceBehavior->Dance();
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

// TODO: передавать unique_ptr