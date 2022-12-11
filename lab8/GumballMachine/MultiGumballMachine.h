#pragma once
#include "IMultiGumballMachine.h"
#include "MultiState/MultiHasQuarterState.h"
#include "MultiState/MultiNoQuarterState.h"
#include "MultiState/MultiSoldOutState.h"
#include "MultiState/MultiSoldState.h"
#include <format>
#include <iostream>
#include <string>

namespace with_state
{
class MultiGumballMachine : private IMultiGumballMachine
{
public:
	const short MAX_QUARTER_COUNT = 5;

	MultiGumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_ballCount(numBalls)
		, m_quarterCount(0)
	{
		if (m_ballCount > 0)
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
		if (m_quarterCount == MAX_QUARTER_COUNT)
		{
			std::cout << "You have reached the limit of inserted quarters. Turn the crank or eject quarters\n";

			return;
		}
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
			m_ballCount, (m_ballCount != 1 ? "s" : ""), m_state->ToString());

		return fmt;
	}

private:
	unsigned GetBallCount() const override
	{
		return m_ballCount;
	}
	void ReleaseBall() override
	{
		if (m_ballCount != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_ballCount;
		}
	}
	void TakeQuarter() override
	{
		if (m_quarterCount != 0)
		{
			std::cout << "Take quarter\n";
			--m_quarterCount;
		}
	}
	void AcceptQuarter() override
	{
		if (m_quarterCount != MAX_QUARTER_COUNT)
		{
			std::cout << "Accept quarter\n";
			++m_quarterCount;
		}
	}
	void RefundQuarter() override
	{
		if (m_quarterCount != 0)
		{
			std::cout << "Refund quarter\n";
			--m_quarterCount;
		}
	}
	unsigned GetQuarterCount() const override
	{
		return m_quarterCount;
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
	unsigned m_ballCount = 0;
	unsigned m_quarterCount = 0;
	MultiSoldState m_soldState;
	MultiSoldOutState m_soldOutState;
	MultiNoQuarterState m_noQuarterState;
	MultiHasQuarterState m_hasQuarterState;
	IState* m_state;
};
} // namespace with_state