#include <sstream>
#include "../GumballMachine/MultiGumballMachineRefillable.h"
#include "../GumballMachine/Menu/MenuFP.h"
using namespace with_state;

void HandleInputReadFail(const std::string& message)
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	throw std::runtime_error(message);
}

unsigned ReadPosition()
{
	std::string numBallsString;
	std::getline(std::cin, numBallsString);

	if (std::cin.fail())
	{
		HandleInputReadFail("Number of balls was expected");
	}

	unsigned numBalls;
	
	std::stringstream ss(numBallsString);
	ss >> numBalls;

	if (ss.fail())
	{
		throw std::runtime_error("Couldn't read number of balls");
	}

	return numBalls;
}

int main()
{
	MultiGumballMachineRefillable gumballMachine(5);
	MenuFP menu;

	menu.AddItem("eject", "Eject all inserted and not used quarters", [&] {
		gumballMachine.EjectQuarter();
	});
	menu.AddItem("insert", "Insert quarter according to the possible gumball machine limit", [&] {
		gumballMachine.InsertQuarter();
	});
	menu.AddItem("turn-crank", "Turn crank and release a gumball if quarter was inserted before", [&] {
		gumballMachine.TurnCrank();
	});
	menu.AddItem("status", "Output a string with all available gumball info", [&] {
		std::cout << gumballMachine.ToString();
	});
	menu.AddItem("refill", "Refill with given amount of gumballs", [&] {
		unsigned numBalls = ReadPosition();
		gumballMachine.Refill(numBalls);
	});

	menu.AddItem("help", "Show instructions", [&] {
		menu.ShowInstructions();
	});

	menu.AddItem("exit", "Exit from this menu", [&] {
		menu.Exit();
	});

	menu.Run();
}