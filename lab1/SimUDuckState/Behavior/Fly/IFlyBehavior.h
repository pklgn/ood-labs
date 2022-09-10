#pragma once

struct IFlyBehavior
{
	virtual bool Fly() = 0;
	virtual ~IFlyBehavior() = default;
};
