#pragma once
#include <string>

namespace with_state
{
struct IStateRefillable
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Refill(unsigned) = 0;
	virtual void Dispense() = 0;
	virtual std::string ToString() const = 0;

	virtual ~IStateRefillable() = default;
};
} // namespace with_state