#include "../../../pch.h"
#include "MacroCommand.h"

void MacroCommand::AddCommand(std::unique_ptr<ICommand>&& command)
{
	m_commands.push_back(std::move(command));
}

void MacroCommand::DoExecute()
{
	for (auto&& command : m_commands)
	{
		command->Execute();
	}
}

void MacroCommand::DoUnexecute()
{
	for (auto&& command : m_commands)
	{
		command->Unexecute();
	}
}
