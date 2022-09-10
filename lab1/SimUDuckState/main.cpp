#include <iostream>
#include "MallardDuck.h"
#include "RedHeadDuck.h"
#include "RubberDuck.h"
#include "DecoyDuck.h"
#include "Behavior/Fly/FlyWithRocketPower.h"
#include "Behavior/Fly/FlyWithWings.h"
#include "Behavior/Fly/FlyNoWay.h"
#include "Behavior/Dance/DanceWaltz.h"
#include "Behavior/Dance/DanceMinuet.h"
#include "Behavior/Dance/DanceNoWay.h"
#include "Behavior/Quack/CommonQuack.h"
#include "Behavior/Quack/Squeak.h"
#include "Behavior/Quack/MuteQuack.h"

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

void PrintDuckFlightsCount(std::ostream& out, const Duck& duck)
{
	out << "Flights count = " << duck.GetFlightsCount() << "\n";
}

void CheckDuck(std::ostream& out, Duck& duck)
{
	PrintDuckFlightsCount(std::cout, duck);
	duck.PerformFly();
	PrintDuckFlightsCount(std::cout, duck);
	duck.PerformQuack();
	duck.PerformDance();

	duck.PerformFly();
	duck.PerformFly();
	duck.Swim();
	duck.Swim();

	duck.SetFlyBehavior(new FlyWithWings);
	duck.PerformFly();
	duck.SetFlyBehavior(new FlyWithRocketPower);
	duck.PerformFly();
	duck.SetFlyBehavior(new FlyNoWay);
	duck.PerformFly();
	PrintDuckFlightsCount(std::cout, duck);

	duck.SetDanceBehavior(new DanceWaltz);
	duck.PerformDance();
	duck.SetDanceBehavior(new DanceMinuet);
	duck.PerformDance();
	duck.SetDanceBehavior(new DanceNoWay);
	duck.PerformDance();

	duck.SetQuackBehavior(new CommonQuack);
	duck.PerformQuack();
	duck.SetQuackBehavior(new Squeak);
	duck.PerformQuack();
	duck.SetQuackBehavior(new MuteQuack);
	duck.PerformQuack();
	out << "\n";
}