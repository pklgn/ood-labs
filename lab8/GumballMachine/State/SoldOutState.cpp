#include "../pch.h"
#include "SoldOutState.h"

namespace with_state
{
SoldOutState::SoldOutState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void SoldOutState::InsertQuarter()
{
	std::cout << "You can't insert a quarter, the machine is sold out\n";
}
void SoldOutState::EjectQuarter()
{
	std::cout << "You can't eject, you haven't inserted a quarter yet\n";
}
void SoldOutState::TurnCrank()
{
	std::cout << "You turned but there's no gumballs\n";
}
void SoldOutState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}
std::string SoldOutState::ToString() const
{
	return "sold out";
}
} // namespace with_state