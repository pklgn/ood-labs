#pragma once
#include "../State/IState.h"
#include "../IMultiGumballMachine.h"

namespace with_state
{
class MultiNoQuarterState : public IState
{
public:
	MultiNoQuarterState(IMultiGumballMachine& gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IMultiGumballMachine& m_gumballMachine;
};
} // namespace with_state