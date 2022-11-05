#include "../pch.h"
#include "History.h"

bool History::CanUndo() const
{
	if (m_nextCommandIndex > 0)
	{
		return true;
	}

	return false;
}

bool History::CanRedo() const
{
	if (m_nextCommandIndex < m_commands.size())
	{
		return true;
	}

	return false;
}

void History::Undo()
{
	if (CanUndo())
	{
		m_commands[m_nextCommandIndex - 1]->Unexecute();
		--m_nextCommandIndex;
	}
}

void History::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute();
		++m_nextCommandIndex;
	}
}

void History::AddAndExecuteCommand(ICommandPtr&& command)
{
	if (CanRedo())
	{
		command->Execute();
		++m_nextCommandIndex;
		m_commands.resize(m_nextCommandIndex);
		m_commands.back() = std::move(command);

		return;
	}

	m_commands.emplace_back(nullptr);
	try
	{
		command->Execute();

		m_commands.back() = std::move(command);
		++m_nextCommandIndex;
	}
	catch (...)
	{
		m_commands.pop_back();
		throw;
	}
}
