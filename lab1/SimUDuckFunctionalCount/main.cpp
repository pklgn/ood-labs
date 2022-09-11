#include <iostream>
#include "MallardDuck.h"
#include "RedHeadDuck.h"
#include "RubberDuck.h"
#include "DecoyDuck.h"
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

void CheckDuck(std::ostream& out, Duck& duck);

int main()
{
	MallardDuck mallardDuck;
	CheckDuck(std::cout, mallardDuck);

	RedHeadDuck redHeadDuck;
	CheckDuck(std::cout, redHeadDuck);

	RubberDuck rubberDuck;
	CheckDuck(std::cout, rubberDuck);

	DecoyDuck decoyDuck;
	CheckDuck(std::cout, decoyDuck);
}

void CheckDuck(std::ostream& out, Duck& duck)
{
	duck.PerformFly();
	duck.PerformQuack();
	duck.PerformDance();

	duck.PerformFly();
	duck.PerformFly();
	duck.Swim();
	duck.Swim();

	auto flyWithWings = GetFlyWithWingsFunction();
	duck.SetFlyBehavior(flyWithWings);
	duck.PerformFly();
	auto flyWithRocketPower = GetFlyWithRocketPowerFunction();
	duck.SetFlyBehavior(flyWithRocketPower);
	duck.PerformFly();
	auto flyNoWay = GetFlyNoWayFunction();
	duck.SetFlyBehavior(flyNoWay);
	duck.PerformFly();

	auto danceWaltz = GetDanceWaltzFunction();
	duck.SetDanceBehavior(danceWaltz);
	duck.PerformDance();
	auto danceMinuet = GetDanceMinuetFunction();
	duck.SetDanceBehavior(danceMinuet);
	duck.PerformDance();
	auto danceNoWay = GetDanceNoWayFunction();
	duck.SetDanceBehavior(danceNoWay);
	duck.PerformDance();

	auto commonQuack = GetMuteQuackFunction();
	duck.SetQuackBehavior(commonQuack);
	duck.PerformQuack();
	auto squeak = GetSqueakFunction();
	duck.SetQuackBehavior(squeak);
	duck.PerformQuack();
	auto muteQuack = GetMuteQuackFunction();
	duck.SetQuackBehavior(muteQuack);
	duck.PerformQuack();
	out << "\n";
}