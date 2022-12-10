#pragma once
#include <string>
#include <format>
#include <iostream>
#include "IGumballMachine.h"
#include "State/HasQuarterState.h"
#include "State/NoQuarterState.h"
#include "State/SoldOutState.h"
#include "State/SoldState.h"

namespace with_state
{
class GumballMachine : private IGumballMachine
{
public:
	GumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}
	std::string ToString() const
	{
		auto fmt = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
)",
			m_count, (m_count != 1 ? "s" : ""), m_state->ToString());

		return fmt;
	}

private:
	unsigned GetBallCount() const
	{
		return m_count;
	}
	virtual void ReleaseBall()
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}
	void SetSoldOutState()
	{
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState()
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState()
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState()
	{
		m_state = &m_hasQuarterState;
	}

private:
	unsigned m_count = 0;
	SoldState m_soldState;
	SoldOutState m_soldOutState;
	NoQuarterState m_noQuarterState;
	HasQuarterState m_hasQuarterState;
	IState* m_state;
};
} // namespace with_state