#include <memory>
#include "DecoyDuck.h"
#include "Behavior/Fly/FlyNoWay.h"
#include "Behavior/Quack/MuteQuack.h"
#include "Behavior/Dance/DanceNoWay.h"

DecoyDuck::DecoyDuck()
{
	m_flyBehavior = std::make_unique<FlyNoWay>();
	m_quackBehavior = std::make_unique<MuteQuack>();
	m_danceBehavior = std::make_unique<DanceNoWay>();
}