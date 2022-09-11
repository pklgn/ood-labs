#include "DecoyDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

DecoyDuck::DecoyDuck()
	: Duck(std::move(GetFlyNoWayFunction()),
		std::move(GetMuteQuackFunction()),
		std::move(GetDanceNoWayFunction()))
{
}