#include <memory>
#include "MallardDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

MallardDuck::MallardDuck()
	: Duck(std::move(GetFlyWithWingsFunction()),
		std::move(GetCommonQuackFunction()),
		std::move(GetDanceWaltzFunction()))
{
}