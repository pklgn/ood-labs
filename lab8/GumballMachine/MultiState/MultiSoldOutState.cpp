#include "../pch.h"
#include "MultiSoldOutState.h"

namespace with_state
{
MultiSoldOutState::MultiSoldOutState(IMultiGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void MultiSoldOutState::InsertQuarter()
{
	std::cout << "You can't insert a quarter, the machine is sold out\n";
}
void MultiSoldOutState::EjectQuarter()
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
void MultiSoldOutState::TurnCrank()
{
	std::cout << "You turned but there's no gumballs\n";
}
void MultiSoldOutState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}
std::string MultiSoldOutState::ToString() const
{
	return "sold out";
}
} // namespace with_state