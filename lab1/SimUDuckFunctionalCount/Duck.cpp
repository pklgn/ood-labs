#include <iostream>
#include "Duck.h"

void Duck::PerformFly()
{
	m_flyBehavior();
}

void Duck::PerformQuack() const
{
	m_quackBehavior();
}

void Duck::PerformDance() const
{
	m_danceBehavior();
}

void Duck::Swim()
{
	std::cout << "Swimming!\n";
}

void Duck::SetFlyBehavior(std::function<void()>& behavior)
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

Duck::Duck(std::function<void()> flyBehavior,
	std::function<void()> quackBehavior,
	std::function<void()> danceBehavior): 
	m_flyBehavior(std::move(flyBehavior))
	, m_quackBehavior(std::move(quackBehavior))
	, m_danceBehavior(std::move(danceBehavior))
{
}