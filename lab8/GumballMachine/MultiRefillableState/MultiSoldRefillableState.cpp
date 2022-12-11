#include "../pch.h"
#include "MultiSoldRefillableState.h"

namespace with_state
{
MultiSoldRefillableState::MultiSoldRefillableState(IMultiGumballMachineRefillable& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void MultiSoldRefillableState::InsertQuarter()
{
	std::cout << "Please wait, we're already giving you a gumball\n";
}
void MultiSoldRefillableState::EjectQuarter()
{
	std::cout << "Please wait until we finish issuing the gumball\n";
}
void MultiSoldRefillableState::TurnCrank()
{
	std::cout << "Turning twice doesn't get you another gumball\n";
}
void MultiSoldRefillableState::Dispense()
{
	m_gumballMachine.ReleaseBall();
	m_gumballMachine.TakeQuarter();
	if (m_gumballMachine.GetBallCount() == 0)
	{
		std::cout << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();

		return;
	}

	if (m_gumballMachine.GetQuarterCount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();

		return;
	}

	m_gumballMachine.SetHasQuarterState();
}
std::string MultiSoldRefillableState::ToString() const
{
	return "delivering a gumball";
}
void MultiSoldRefillableState::Refill(unsigned numBalls)
{
	std::cout << "Unable to refill while issuing the gumball\n";
}
} // namespace with_state