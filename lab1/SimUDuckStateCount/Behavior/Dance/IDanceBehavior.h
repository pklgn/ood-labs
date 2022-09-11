#pragma once

struct IDanceBehavior
{
	virtual void Dance() = 0;
	virtual ~IDanceBehavior() = default;
};