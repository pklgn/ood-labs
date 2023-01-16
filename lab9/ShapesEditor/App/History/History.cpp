#include "../../pch.h"
#include "History.h"

bool History::CanUndo() const
{
	return m_nextCommandIndex > 0;
}

bool History::CanRedo() const
{
	return m_nextCommandIndex < m_commands.size();
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
	//стираем те команды, которые могли бы быть перевыполнены с помощью redo
	if (CanRedo())
	{
		command->Execute();
		++m_nextCommandIndex;
		m_commands.resize(m_nextCommandIndex);
		m_commands.back() = std::move(command);

		return;
	}

	//иначе расширяем историю команд
	m_commands.emplace_back(nullptr);
	try
	{
		command->Execute();

		m_commands.back() = std::move(command);
		if (COMMANDS_DEPTH_LEVEL < m_commands.size())
		{
			m_commands.pop_front();
		}
		else
		{
			++m_nextCommandIndex;
		}
	}
	catch (...)
	{
		m_commands.pop_back();
		throw;
	}
}
