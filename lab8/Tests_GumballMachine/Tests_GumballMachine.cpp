#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <format>
#include <sstream>
#include <iostream>
#include "../GumballMachine/GumballMachine.h"

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
