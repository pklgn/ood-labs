#include "RubberDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

RubberDuck::RubberDuck()
	: Duck(std::move(GetFlyNoWayFunction()),
		std::move(GetSqueakFunction()),
		std::move(GetDanceNoWayFunction()))
{
}