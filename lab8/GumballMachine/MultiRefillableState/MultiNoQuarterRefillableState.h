#pragma once
#include "IStateRefillable.h"
#include "../IMultiGumballMachineRefillable.h"

namespace with_state
{
class MultiNoQuarterRefillableState : public IStateRefillable
{
public:
	MultiNoQuarterRefillableState(IMultiGumballMachineRefillable& gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Refill(unsigned) override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IMultiGumballMachineRefillable& m_gumballMachine;
};
} // namespace with_state