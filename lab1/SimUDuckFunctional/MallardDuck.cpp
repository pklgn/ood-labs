#include <memory>
#include "MallardDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

MallardDuck::MallardDuck()
{
	m_flyBehavior = GetFlyWithWingsFunction();
	m_quackBehavior = GetCommonQuackFunction();
	m_danceBehavior = GetDanceWaltzFunction();
}