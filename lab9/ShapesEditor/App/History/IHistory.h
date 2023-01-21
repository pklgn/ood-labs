#pragma once

#include "../Command/ICommand.h"

class IHistory
{
public:
	virtual bool CanUndo() const = 0;
	virtual bool CanRedo() const = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;
};