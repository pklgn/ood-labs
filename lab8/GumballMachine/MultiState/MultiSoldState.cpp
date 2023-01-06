#include "../pch.h"
#include "MultiSoldState.h"

namespace with_state
{
MultiSoldState::MultiSoldState(IMultiGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void MultiSoldState::InsertQuarter()
{
	std::cout << "Please wait, we're already giving you a gumball\n";
}
void MultiSoldState::EjectQuarter()
{
	std::cout << "Please wait until we finish issuing the gumball\n";
}
void MultiSoldState::TurnCrank()
{
	std::cout << "Turning twice doesn't get you another gumball\n";
}
void MultiSoldState::Dispense()
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
std::string MultiSoldState::ToString() const
{
	return "delivering a gumball";
}
} // namespace with_state