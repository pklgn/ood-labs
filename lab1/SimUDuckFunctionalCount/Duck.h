#pragma once
#include <memory>
#include <functional>
#include "Behavior/FlyStrategies.h"
#include "Behavior/QuackStrategies.h"
#include "Behavior/DanceStrategies.h"

class Duck
{
public:
	virtual ~Duck() = default;

	void PerformFly();
	void PerformQuack() const;
	void PerformDance() const;

	void Swim();

	void SetFlyBehavior(std::function<void()>&);
	void SetQuackBehavior(std::function<void()>&);
	void SetDanceBehavior(std::function<void()>&);

protected:
	std::function<void()> m_flyBehavior;
	std::function<void()> m_quackBehavior;
	std::function<void()> m_danceBehavior;

	Duck(std::function<void()>, std::function<void()>, std::function<void()>);
};