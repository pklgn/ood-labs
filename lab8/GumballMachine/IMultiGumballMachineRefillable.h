#pragma once
#include "IMultiGumballMachine.h"

namespace with_state
{
struct IMultiGumballMachineRefillable : public IMultiGumballMachine
{
	virtual void RefillBalls(unsigned) = 0;
};
} // namespace with_state