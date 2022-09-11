#include "DecoyDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

DecoyDuck::DecoyDuck()
{
	m_flyBehavior = GetFlyNoWayFunction();
	m_quackBehavior = GetMuteQuackFunction();
	m_danceBehavior = GetDanceNoWayFunction();
}