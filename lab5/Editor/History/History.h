#pragma once
#include <deque>

#include "../Command/ICommand.h"

class History
{
public:
	const size_t commandsDepthLevel = 10;

	bool CanUndo() const;
	bool CanRedo() const;

	void Undo();
	void Redo();

	void AddAndExecuteCommand(ICommandPtr&&);

private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};

//TODO: сделать интерфейс истории