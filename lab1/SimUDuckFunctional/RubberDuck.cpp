#include "RubberDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

RubberDuck::RubberDuck()
{
	m_flyBehavior = GetFlyNoWayFunction();
	m_quackBehavior = GetSqueakFunction();
	m_danceBehavior = GetDanceNoWayFunction();
}