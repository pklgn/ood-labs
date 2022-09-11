#pragma once
#include <memory>
#include "Behavior/Fly/IFlyBehavior.h"
#include "Behavior/Quack/IQuackBehavior.h"
#include "Behavior/Dance/IDanceBehavior.h"

class Duck
{
public:
	virtual ~Duck() = default;

	void PerformFly();
	void PerformQuack() const;
	void PerformDance() const;

	void Swim();

	void SetFlyBehavior(IFlyBehavior*);
	void SetQuackBehavior(IQuackBehavior*);
	void SetDanceBehavior(IDanceBehavior*);
protected:
	Duck() = default;

	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};
