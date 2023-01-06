#include "../pch.h"
#include "MultiHasQuarterState.h"

namespace with_state
{
MultiHasQuarterState::MultiHasQuarterState(IMultiGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void MultiHasQuarterState::InsertQuarter()
{
	std::cout << "You inserted another quarter\n";
	m_gumballMachine.AcceptQuarter();
}

void MultiHasQuarterState::EjectQuarter()
{
	std::cout << "Refund off all inserted quarters...\n";
	auto quarterCount = m_gumballMachine.GetQuarterCount();
	for (size_t i = 0; i < quarterCount; ++i)
	{
		m_gumballMachine.RefundQuarter();
	}
	m_gumballMachine.SetNoQuarterState();
}

void MultiHasQuarterState::TurnCrank()
{
	std::cout << "You turned...\n";
	m_gumballMachine.SetSoldState();
}

void MultiHasQuarterState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}

std::string MultiHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}
} // namespace with_state