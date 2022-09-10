#include <memory>
#include "RedHeadDuck.h"
#include "Behavior/Fly/FlyWithWings.h"
#include "Behavior/Quack/CommonQuack.h"
#include "Behavior/Dance/DanceMinuet.h"

RedHeadDuck::RedHeadDuck()
{
	m_flyBehavior = std::make_unique<FlyWithWings>();
	m_quackBehavior = std::make_unique<CommonQuack>();
	m_danceBehavior = std::make_unique<DanceMinuet>();
}