#include "RedHeadDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

RedHeadDuck::RedHeadDuck()
	: Duck(std::move(GetFlyWithWingsFunction()),
		std::move(GetCommonQuackFunction()),
		std::move(GetDanceMinuetFunction()))
{
}