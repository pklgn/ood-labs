#include "../pch.h"
#include "AbstractCommand.h"


void AbstractCommand::Execute()
{
	if (!m_executed)
	{
		DoExecute();
		m_executed = true;
	}
}

void AbstractCommand::Unexecute()
{
	if (m_executed)
	{
		DoUnexecute();
		m_executed = false;
	}
}

bool AbstractCommand::WasExecuted()
{
	return m_executed;
}
