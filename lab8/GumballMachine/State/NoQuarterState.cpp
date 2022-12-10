#include "../pch.h"
#include "NoQuarterState.h"

namespace with_state
{
NoQuarterState::NoQuarterState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void NoQuarterState::InsertQuarter()
{
	std::cout << "You inserted a quarter\n";
	m_gumballMachine.SetHasQuarterState();
}
void NoQuarterState::EjectQuarter()
{
	std::cout << "You haven't inserted a quarter\n";
}
void NoQuarterState::TurnCrank()
{
	std::cout << "You turned but there's no quarter\n";
}
void NoQuarterState::Dispense()
{
	std::cout << "You need to pay first\n";
}
std::string NoQuarterState::ToString() const
{
	return "waiting for quarter";
}
} // namespace with_state