#pragma once
#include "IHistory.h"

class ICommandsContainer
{
public:
	virtual void AddAndExecuteCommand(ICommandPtr&&) = 0;
};