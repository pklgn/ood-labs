#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../GumballMachine/GumballMachine.h"
#include "../GumballMachine/MultiGumballMachine.h"
#include "../GumballMachine/MultiGumballMachineRefillable.h"
#include "../GumballMachine/Naive/NaiveMultiGumballMachine.h"
#include <format>
#include <iostream>
#include <sstream>

using namespace with_state;

class IsSameGumballMachineMatcher : public Catch::Matchers::Impl::MatcherBase<GumballMachine>
{
public:
	IsSameGumballMachineMatcher(unsigned count, const std::string& state)
		: m_count(count)
		, m_state(state)
	{
	}

	bool match(GumballMachine const& in) const override
	{
		auto expectedRepresentation = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
)",
			m_count, (m_count != 1 ? "s" : ""), m_state);
					
		return in.ToString() == expectedRepresentation;
	}

	std::string describe() const override
	{
		std::ostringstream ss;
		ss << "is have ball count equals to " << m_count << " and state such as " << m_state;
		return ss.str();
	}

private:
	unsigned m_count;
	const std::string& m_state;
};

IsSameGumballMachineMatcher IsSameGumballMachine(unsigned count, const std::string& state)
{
	return { count, state };
}

TEST_CASE("Act when NO QUARTER")
{
	auto numBalls = 5;
	GumballMachine gumballMachine(numBalls);

	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = 5;
		auto expectedState = "waiting for quarter";

		gumballMachine.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You haven't inserted a quarter\n");
		REQUIRE_THAT(gumballMachine, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = 5;
		auto expectedState = "waiting for turn of crank";

		gumballMachine.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You inserted a quarter\n");
		REQUIRE_THAT(gumballMachine, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = 5;
		auto expectedState = "waiting for quarter";

		gumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned but there's no quarter\n"
							 "You need to pay first\n");
		REQUIRE_THAT(gumballMachine, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	std::cout.rdbuf(stdoutBuffer);
}

TEST_CASE("Act when HAS QUARTER")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	auto numBalls = 2;
	GumballMachine gumballMachine(numBalls);
	gumballMachine.InsertQuarter();

	oss.str("");

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = numBalls;
		auto expectedState = "waiting for quarter";

		gumballMachine.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Quarter returned\n");
		REQUIRE_THAT(gumballMachine, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = numBalls;
		auto expectedState = "waiting for turn of crank";

		gumballMachine.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You can't insert another quarter\n");
		REQUIRE_THAT(gumballMachine, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = numBalls - 1;
		auto expectedState = "waiting for quarter";

		gumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned...\n"
							 "A gumball comes rolling out the slot...\n");
		REQUIRE_THAT(gumballMachine, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	SECTION("Trying to turn crank when single gumball remain")
	{
		gumballMachine.TurnCrank();

		gumballMachine.InsertQuarter();
		auto expectedNumBalls = 0;
		auto expectedState = "sold out";
		oss.str("");
		
		gumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned...\n"
							 "A gumball comes rolling out the slot...\n"
							 "Oops, out of gumballs\n");
		REQUIRE_THAT(gumballMachine, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	std::cout.rdbuf(stdoutBuffer);
}

TEST_CASE("Act when SOLD OUT")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	GumballMachine gumballMachineEmpty(0);

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = 0;
		auto expectedState = "sold out";

		gumballMachineEmpty.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You can't eject, you haven't inserted a quarter yet\n");
		REQUIRE_THAT(gumballMachineEmpty, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = 0;
		auto expectedState = "sold out";

		gumballMachineEmpty.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You can't insert a quarter, the machine is sold out\n");
		REQUIRE_THAT(gumballMachineEmpty, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = 0;
		auto expectedState = "sold out";

		gumballMachineEmpty.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned but there's no gumballs\n"
							 "No gumball dispensed\n");
		REQUIRE_THAT(gumballMachineEmpty, IsSameGumballMachine(expectedNumBalls, expectedState));
	}

	std::cout.rdbuf(stdoutBuffer);
}

template <typename T>
class IsSameMultiGumballMachineMatcher : public Catch::Matchers::Impl::MatcherBase<T>
{
public:
	IsSameMultiGumballMachineMatcher(unsigned ballCount, const std::string& state, unsigned quarterCount)
		: m_ballCount(ballCount)
		, m_state(state)
		, m_quarterCount(quarterCount)
	{
	}

	bool match(T const& in) const override
	{
		auto expectedRepresentation = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
Quarter amount is {}
)",
			m_ballCount, (m_ballCount != 1 ? "s" : ""), m_state, m_quarterCount);

		return in.ToString() == expectedRepresentation;
	}

	std::string describe() const override
	{
		std::ostringstream ss;
		ss << "is have ball count equals to " << m_ballCount
		   << "state such as " << m_state
		   << "and quarter count equals " << m_quarterCount;
		return ss.str();
	}

private:
	unsigned m_ballCount;
	const std::string& m_state;
	unsigned m_quarterCount;
};

template <typename T>
IsSameMultiGumballMachineMatcher<T> IsSameMultiGumballMachine(unsigned ballCount, const std::string& state, unsigned quarterCount)
{
	return { ballCount, state, quarterCount };
}

// Multi tests

TEST_CASE("Act when NO QUARTER for multi gumball machine")
{
	auto numBalls = 5;
	auto numQuarters = 0;
	MultiGumballMachine multiGumballMachine(numBalls);

	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = 5;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		multiGumballMachine.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You haven't inserted any quarters\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = 5;
		auto expectedNumQuarters = 1;
		auto expectedState = "waiting for turn of crank";

		multiGumballMachine.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You inserted a quarter\n"
							 "Accept quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = 5;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		multiGumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned but there's no quarter\n"
							 "You need to pay first\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	std::cout.rdbuf(stdoutBuffer);
}

TEST_CASE("Act when HAS QUARTER for multi gumball machine")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	auto numBalls = 2;
	MultiGumballMachine multiGumballMachine(numBalls);
	multiGumballMachine.InsertQuarter();

	oss.str("");

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = numBalls;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		multiGumballMachine.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Refund off all inserted quarters...\n"
							 "Refund quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = numBalls;
		auto expectedNumQuarters = 2;
		auto expectedState = "waiting for turn of crank";

		multiGumballMachine.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You inserted another quarter\n"
							 "Accept quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to insert quarter and exceed quarters limit")
	{
		multiGumballMachine.InsertQuarter();
		multiGumballMachine.InsertQuarter();
		multiGumballMachine.InsertQuarter();
		multiGumballMachine.InsertQuarter();
		auto expectedNumBalls = numBalls;
		auto expectedNumQuarters = 5;
		auto expectedState = "waiting for turn of crank";
		oss.str("");

		multiGumballMachine.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You have reached the limit of inserted quarters. Turn the crank or eject quarters\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = numBalls - 1;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		multiGumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned...\n"
							 "A gumball comes rolling out the slot...\n"
							 "Take quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank when several quarters were inserted")
	{
		multiGumballMachine.InsertQuarter();
		auto expectedNumBalls = numBalls - 1;
		auto expectedNumQuarters = 1;
		auto expectedState = "waiting for turn of crank";
		oss.str("");

		multiGumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned...\n"
							 "A gumball comes rolling out the slot...\n"
							 "Take quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank when single gumball remain")
	{
		multiGumballMachine.TurnCrank();

		multiGumballMachine.InsertQuarter();
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";
		oss.str("");

		multiGumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned...\n"
							 "A gumball comes rolling out the slot...\n"
							 "Take quarter\n"
							 "Oops, out of gumballs\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	std::cout.rdbuf(stdoutBuffer);
}

TEST_CASE("Act when SOLD OUT for multi gumball machine")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	MultiGumballMachine multiGumballMachineEmpty(0);

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";

		multiGumballMachineEmpty.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Nothing to refund\n");
		REQUIRE_THAT(multiGumballMachineEmpty, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";

		multiGumballMachineEmpty.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You can't insert a quarter, the machine is sold out\n");
		REQUIRE_THAT(multiGumballMachineEmpty, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";

		multiGumballMachineEmpty.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned but there's no gumballs\n"
							 "No gumball dispensed\n");
		REQUIRE_THAT(multiGumballMachineEmpty, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	std::cout.rdbuf(stdoutBuffer);
}

TEST_CASE("Act when SOLD OUT for multi gumball machine and inserted quarters")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	MultiGumballMachine multiGumballMachine(2);
	multiGumballMachine.InsertQuarter();
	multiGumballMachine.InsertQuarter();
	multiGumballMachine.InsertQuarter();
	multiGumballMachine.InsertQuarter();

	multiGumballMachine.TurnCrank();
	multiGumballMachine.TurnCrank();
	oss.str("");

	SECTION("Refund remain quarters")
	{
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";
		
		multiGumballMachine.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Refund off all inserted quarters...\n"
							 "Refund quarter\n"
							 "Refund quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}
}

// Multi naive tests

TEST_CASE("Act when NO QUARTER for naive multi gumball machine")
{
	auto numBalls = 5;
	auto numQuarters = 0;
	naive::MultiGumballMachine multiGumballMachine(numBalls);

	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = 5;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		multiGumballMachine.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You haven't inserted any quarters\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = 5;
		auto expectedNumQuarters = 1;
		auto expectedState = "waiting for turn of crank";

		multiGumballMachine.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You inserted a quarter\n"
							 "Accept quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = 5;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		multiGumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned but there's no quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	std::cout.rdbuf(stdoutBuffer);
}

TEST_CASE("Act when HAS QUARTER for naive multi gumball machine")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	auto numBalls = 2;
	naive::MultiGumballMachine multiGumballMachine(numBalls);
	multiGumballMachine.InsertQuarter();

	oss.str("");

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = numBalls;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		multiGumballMachine.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Refund off all inserted quarters...\n"
							 "Refund quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = numBalls;
		auto expectedNumQuarters = 2;
		auto expectedState = "waiting for turn of crank";

		multiGumballMachine.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You inserted another quarter\n"
							 "Accept quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to insert quarter and exceed quarters limit")
	{
		multiGumballMachine.InsertQuarter();
		multiGumballMachine.InsertQuarter();
		multiGumballMachine.InsertQuarter();
		multiGumballMachine.InsertQuarter();
		auto expectedNumBalls = numBalls;
		auto expectedNumQuarters = 5;
		auto expectedState = "waiting for turn of crank";
		oss.str("");

		multiGumballMachine.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You have reached the limit of inserted quarters. Turn the crank or eject quarters\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = numBalls - 1;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		multiGumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned...\n"
							 "A gumball comes rolling out the slot...\n"
							 "Take quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank when several quarters were inserted")
	{
		multiGumballMachine.InsertQuarter();
		auto expectedNumBalls = numBalls - 1;
		auto expectedNumQuarters = 1;
		auto expectedState = "waiting for turn of crank";
		oss.str("");

		multiGumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned...\n"
							 "A gumball comes rolling out the slot...\n"
							 "Take quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank when single gumball remain")
	{
		multiGumballMachine.TurnCrank();

		multiGumballMachine.InsertQuarter();
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";
		oss.str("");

		multiGumballMachine.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned...\n"
							 "A gumball comes rolling out the slot...\n"
							 "Take quarter\n"
							 "Oops, out of gumballs\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	std::cout.rdbuf(stdoutBuffer);
}

TEST_CASE("Act when SOLD OUT for naive multi gumball machine")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	naive::MultiGumballMachine multiGumballMachineEmpty(0);

	SECTION("Trying to eject quarter")
	{
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";

		multiGumballMachineEmpty.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Nothing to refund\n");
		REQUIRE_THAT(multiGumballMachineEmpty, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to insert quarter")
	{
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";

		multiGumballMachineEmpty.InsertQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You can't insert a quarter, the machine is sold out\n");
		REQUIRE_THAT(multiGumballMachineEmpty, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Trying to turn crank")
	{
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";

		multiGumballMachineEmpty.TurnCrank();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "You turned but there's no gumballs\n");
		REQUIRE_THAT(multiGumballMachineEmpty, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	std::cout.rdbuf(stdoutBuffer);
}

TEST_CASE("Act when SOLD OUT for naive multi gumball machine and inserted quarters")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());

	naive::MultiGumballMachine multiGumballMachine(2);
	multiGumballMachine.InsertQuarter();
	multiGumballMachine.InsertQuarter();
	multiGumballMachine.InsertQuarter();
	multiGumballMachine.InsertQuarter();

	multiGumballMachine.TurnCrank();
	multiGumballMachine.TurnCrank();
	oss.str("");

	SECTION("Refund remain quarters")
	{
		auto expectedNumBalls = 0;
		auto expectedNumQuarters = 0;
		auto expectedState = "sold out";

		multiGumballMachine.EjectQuarter();

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Refund off all inserted quarters...\n"
							 "Refund quarter\n"
							 "Refund quarter\n");
		REQUIRE_THAT(multiGumballMachine, IsSameMultiGumballMachine<naive::MultiGumballMachine>(expectedNumBalls, expectedState, expectedNumQuarters));
	}
}

TEST_CASE("Refill multi gumball machine in every possible way")
{
	auto stdoutBuffer = std::cout.rdbuf();
	std::ostringstream oss;
	std::cout.rdbuf(oss.rdbuf());
	auto numBalls = 2;
	MultiGumballMachineRefillable gumballMachine(numBalls);
	MultiGumballMachineRefillable gumballMachineEmpty(0);

	SECTION("Refill when NO QUARTER")
	{
		auto expectedNumBalls = 5;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";

		gumballMachine.Refill(5);

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Refill machine with 5 balls\n");
		REQUIRE_THAT(gumballMachine, IsSameMultiGumballMachine<MultiGumballMachineRefillable>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Refill when HAS QUARTER")
	{
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
		auto expectedNumBalls = 6;
		auto expectedNumQuarters = 2;
		auto expectedState = "waiting for turn of crank";
		oss.str("");

		gumballMachine.Refill(6);

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Refill machine with 6 balls\n");
		REQUIRE_THAT(gumballMachine, IsSameMultiGumballMachine<MultiGumballMachineRefillable>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Refill when SOLD OUT")
	{
		auto expectedNumBalls = 6;
		auto expectedNumQuarters = 0;
		auto expectedState = "waiting for quarter";
		oss.str("");

		gumballMachineEmpty.Refill(6);

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Refill machine with 6 balls\n");
		REQUIRE_THAT(gumballMachineEmpty, IsSameMultiGumballMachine<MultiGumballMachineRefillable>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	SECTION("Refill when SOLD OUT and have inserted quarters")
	{
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
		gumballMachine.TurnCrank();
		gumballMachine.TurnCrank();
		auto expectedNumBalls = 6;
		auto expectedNumQuarters = 1;
		auto expectedState = "waiting for turn of crank";
		oss.str("");

		gumballMachine.Refill(6);

		std::cout.rdbuf(stdoutBuffer);
		REQUIRE(oss.str() == "Refill machine with 6 balls\n");
		REQUIRE_THAT(gumballMachine, IsSameMultiGumballMachine<MultiGumballMachineRefillable>(expectedNumBalls, expectedState, expectedNumQuarters));
	}

	std::cout.rdbuf(stdoutBuffer);
}