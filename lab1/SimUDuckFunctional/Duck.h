#pragma once
#include <memory>
#include <functional>
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

class Duck
{
public:
	using count_type = size_t;

	virtual ~Duck() = default;

	void PerformFly();
	void PerformQuack() const;
	void PerformDance() const;

	void Swim();

	void SetFlyBehavior(std::function<bool()>&);
	void SetQuackBehavior(std::function<void()>&);
	void SetDanceBehavior(std::function<void()>&);

	count_type GetFlightsCount() const;

protected:
	Duck() = default;

	count_type m_flightsCount = 0;

	std::function<bool()> m_flyBehavior;
	std::function<void()> m_quackBehavior;
	std::function<void()> m_danceBehavior;
};