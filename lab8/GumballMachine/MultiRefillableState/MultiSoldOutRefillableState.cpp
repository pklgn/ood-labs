#include "../pch.h"
#include "MultiSoldOutRefillableState.h"

namespace with_state
{
MultiSoldOutRefillabeState::MultiSoldOutRefillabeState(IMultiGumballMachineRefillable& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void MultiSoldOutRefillabeState::InsertQuarter()
{
	std::cout << "You can't insert a quarter, the machine is sold out\n";
}
void MultiSoldOutRefillabeState::EjectQuarter()
{
	auto quarterCount = m_gumballMachine.GetQuarterCount();
	if (quarterCount == 0)
	{
		std::cout << "Nothing to refund\n";

		return;
	}

	std::cout << "Refund off all inserted quarters...\n";
	for (size_t i = 0; i < quarterCount; ++i)
	{
		m_gumballMachine.RefundQuarter();
	}
}
void MultiSoldOutRefillabeState::TurnCrank()
{
	std::cout << "You turned but there's no gumballs\n";
}
void MultiSoldOutRefillabeState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}
std::string MultiSoldOutRefillabeState::ToString() const
{
	return "sold out";
}
void MultiSoldOutRefillabeState::Refill(unsigned numBalls)
{
	m_gumballMachine.RefillBalls(numBalls);
	std::cout << "Refill machine with " << numBalls << " balls\n";
	if (m_gumballMachine.GetQuarterCount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();

		return;
	}

	m_gumballMachine.SetHasQuarterState();
}
} // namespace with_state