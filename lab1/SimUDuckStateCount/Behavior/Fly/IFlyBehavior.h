#pragma once

struct IFlyBehavior
{
	virtual void Fly() = 0;
	virtual ~IFlyBehavior() = default;
};
