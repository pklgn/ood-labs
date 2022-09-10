#include "RubberDuck.h"
#include "Behavior/Fly/FlyNoWay.h"
#include "Behavior/Quack/Squeak.h"
#include "Behavior/Dance/DanceNoWay.h"

RubberDuck::RubberDuck()
{
	m_flyBehavior = std::make_unique<FlyNoWay>();
	m_quackBehavior = std::make_unique<Squeak>();
	m_danceBehavior = std::make_unique<DanceNoWay>();
}