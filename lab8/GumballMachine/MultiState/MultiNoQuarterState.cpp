#include "../pch.h"
#include "MultiNoQuarterState.h"

namespace with_state
{
MultiNoQuarterState::MultiNoQuarterState(IMultiGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void MultiNoQuarterState::InsertQuarter()
{
	std::cout << "You inserted a quarter\n";
	m_gumballMachine.AcceptQuarter();
	m_gumballMachine.SetHasQuarterState();
}
void MultiNoQuarterState::EjectQuarter()
{
	std::cout << "You haven't inserted any quarters\n";
}
void MultiNoQuarterState::TurnCrank()
{
	std::cout << "You turned but there's no quarter\n";
}
void MultiNoQuarterState::Dispense()
{
	std::cout << "You need to pay first\n";
}
std::string MultiNoQuarterState::ToString() const
{
	return "waiting for quarter";
}
} // namespace with_state