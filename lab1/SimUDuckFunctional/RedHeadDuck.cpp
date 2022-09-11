#include "RedHeadDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

RedHeadDuck::RedHeadDuck()
{
	m_flyBehavior = GetFlyWithWingsFunction();
	m_quackBehavior = GetCommonQuackFunction();
	m_danceBehavior = GetDanceMinuetFunction();
}