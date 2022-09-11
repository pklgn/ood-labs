#include <memory>
#include "MallardDuck.h"
#include "Behavior/Fly/FlyWithWings.h"
#include "Behavior/Quack/CommonQuack.h"
#include "Behavior/Dance/DanceWaltz.h"

MallardDuck::MallardDuck()
{
	m_flyBehavior = std::make_unique<FlyWithWings>();
	m_quackBehavior = std::make_unique<CommonQuack>();
	m_danceBehavior = std::make_unique<DanceWaltz>();
}