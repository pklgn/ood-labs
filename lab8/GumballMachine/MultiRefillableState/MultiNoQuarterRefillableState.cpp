#include "../pch.h"
#include "MultiNoQuarterRefillableState.h"

namespace with_state
{
MultiNoQuarterRefillableState::MultiNoQuarterRefillableState(IMultiGumballMachineRefillable& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void MultiNoQuarterRefillableState::InsertQuarter()
{
	std::cout << "You inserted a quarter\n";
	m_gumballMachine.AcceptQuarter();
	m_gumballMachine.SetHasQuarterState();
}
void MultiNoQuarterRefillableState::EjectQuarter()
{
	std::cout << "You haven't inserted any quarters\n";
}
void MultiNoQuarterRefillableState::TurnCrank()
{
	std::cout << "You turned but there's no quarter\n";
}
void MultiNoQuarterRefillableState::Refill(unsigned numBalls)
{
	m_gumballMachine.RefillBalls(numBalls);
	std::cout << "Refill machine with " << numBalls << " balls\n";
}
void MultiNoQuarterRefillableState::Dispense()
{
	std::cout << "You need to pay first\n";
}
std::string MultiNoQuarterRefillableState::ToString() const
{
	return "waiting for quarter";
}
} // namespace with_state