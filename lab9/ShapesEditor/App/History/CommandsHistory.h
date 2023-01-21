#pragma once
#include <deque>

#include "ICommandsContainer.h"

class CommandsHistory : public IHistory, public ICommandsContainer
{
public:
	const size_t COMMANDS_DEPTH_LEVEL = 5;

	bool CanUndo() const override;
	bool CanRedo() const override;

	void Undo() override;
	void Redo() override;

	void AddAndExecuteCommand(ICommandPtr&&) override;

private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};
