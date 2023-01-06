#include "../pch.h"
#include "MultiHasQuarterRefillableState.h"

namespace with_state
{
MultiHasQuarterRefillableState::MultiHasQuarterRefillableState(IMultiGumballMachineRefillable& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void MultiHasQuarterRefillableState::InsertQuarter()
{
	std::cout << "You inserted another quarter\n";
	m_gumballMachine.AcceptQuarter();
}

void MultiHasQuarterRefillableState::EjectQuarter()
{
	std::cout << "Refund off all inserted quarters...\n";
	auto quarterCount = m_gumballMachine.GetQuarterCount();
	for (size_t i = 0; i < quarterCount; ++i)
	{
		m_gumballMachine.RefundQuarter();
	}
	m_gumballMachine.SetNoQuarterState();
}

void MultiHasQuarterRefillableState::TurnCrank()
{
	std::cout << "You turned...\n";
	m_gumballMachine.SetSoldState();
}

void MultiHasQuarterRefillableState::Refill(unsigned numBalls)
{
	m_gumballMachine.RefillBalls(numBalls);
	std::cout << "Refill machine with " << numBalls << " balls\n";
}

void MultiHasQuarterRefillableState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}

std::string MultiHasQuarterRefillableState::ToString() const
{
	return "waiting for turn of crank";
}
} // namespace with_state