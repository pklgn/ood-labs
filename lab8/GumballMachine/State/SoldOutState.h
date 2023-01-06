#pragma once
#include "IState.h"
#include "../IGumballMachine.h"

namespace with_state
{
class SoldOutState : public IState
{
public:
	SoldOutState(IGumballMachine& gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;
};
} // namespace with_state