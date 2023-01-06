#include "../pch.h"
#include "SoldState.h"

namespace with_state
{
SoldState::SoldState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void SoldState::InsertQuarter()
{
	std::cout << "Please wait, we're already giving you a gumball\n";
}
void SoldState::EjectQuarter()
{
	std::cout << "Sorry you already turned the crank\n";
}
void SoldState::TurnCrank()
{
	std::cout << "Turning twice doesn't get you another gumball\n";
}
void SoldState::Dispense()
{
	m_gumballMachine.ReleaseBall();
	if (m_gumballMachine.GetBallCount() == 0)
	{
		std::cout << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else
	{
		m_gumballMachine.SetNoQuarterState();
	}
}
std::string SoldState::ToString() const
{
	return "delivering a gumball";
}
} // namespace with_state