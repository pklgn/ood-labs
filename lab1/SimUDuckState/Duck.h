#pragma once
#include <memory>
#include "Behavior/Fly/IFlyBehavior.h"
#include "Behavior/Quack/IQuackBehavior.h"
#include "Behavior/Dance/IDanceBehavior.h"

using count_type = size_t;

class Duck
{
public:
	using count_type = size_t;

	virtual ~Duck() = default;

	void PerformFly();
	void PerformQuack() const;
	void PerformDance() const;

	void Swim();

	void SetFlyBehavior(IFlyBehavior*);
	void SetQuackBehavior(IQuackBehavior*);
	void SetDanceBehavior(IDanceBehavior*);

	count_type GetFlightsCount() const;
protected:
	Duck() = default;

	count_type m_flightsCount;

	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};
