#pragma once

#include <format>
#include <iostream>

namespace naive
{
class MultiGumballMachine
{
public:
	static const unsigned MAX_QUARTER_COUNT = 5;
	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoQuarter, // Нет монетки
		HasQuarter, // Есть монетка
		Sold, // Монетка выдана
	};

	MultiGumballMachine(unsigned ballCount)
		: m_ballCount(ballCount)
		, m_quarterCount(0)
		, m_state(ballCount > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			cout << "You inserted a quarter\n";
			++m_quarterCount;
			cout << "Accept quarter\n";
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			if (m_quarterCount == MAX_QUARTER_COUNT)
			{
				cout << "You have reached the limit of inserted quarters. Turn the crank or eject quarters\n";
			}
			else
			{
				cout << "You inserted another quarter\n";
				++m_quarterCount;
				cout << "Accept quarter\n";
			}
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;

		auto quarterCount = m_quarterCount;

		switch (m_state)
		{
		case State::HasQuarter:
			cout << "Refund off all inserted quarters...\n";
			for (size_t i = 0; i < quarterCount; ++i)
			{
				std::cout << "Refund quarter\n";
				--m_quarterCount;
			}
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted any quarters\n";
			break;
		case State::Sold:
			cout << "Please wait until we finish issuing the gumball\n";
			break;
		case State::SoldOut:
			if (m_quarterCount == 0)
			{
				cout << "Nothing to refund\n";

				return;
			}
			cout << "Refund off all inserted quarters...\n";
			for (size_t i = 0; i < quarterCount; ++i)
			{
				std::cout << "Refund quarter\n";
				--m_quarterCount;
			}
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			cout << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_ballCount = numBalls;
		m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
	}

	std::string ToString() const
	{
		std::string state =
			(m_state == State::SoldOut)	   ? "sold out" :
			(m_state == State::NoQuarter)  ? "waiting for quarter" :
			(m_state == State::HasQuarter) ? "waiting for turn of crank"
										   : "delivering a gumball";

		auto fmt = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
Quarter amount is {}
)",
			m_ballCount, (m_ballCount != 1 ? "s" : ""), state, m_quarterCount);

		return fmt;
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot...\n";
			--m_ballCount;
			--m_quarterCount;
			cout << "Take quarter\n";
			if (m_ballCount == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				if (m_quarterCount == 0)
				{
					m_state = State::NoQuarter;
				}
				else
				{
					m_state = State::HasQuarter;
				}
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
			break;
		}
	}

	unsigned m_ballCount; // Количество шариков
	unsigned m_quarterCount;
	State m_state = State::SoldOut;
};
} // namespace naive