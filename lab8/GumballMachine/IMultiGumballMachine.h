#pragma once
#include "IGumballMachine.h"

namespace with_state
{
struct IMultiGumballMachine : public IGumballMachine
{
	virtual void TakeQuarter() = 0;
	virtual void AcceptQuarter() = 0;
	virtual void RefundQuarter() = 0;
	virtual unsigned GetQuarterCount() const = 0;
};
} // namespace with_state