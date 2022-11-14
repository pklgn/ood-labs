#include "../../pch.h"
#include "SetTitleCommand.h"

SetTitleCommand::SetTitleCommand(std::string& target, const std::string& newValue)
	: m_target(target)
	, m_newValue(newValue)
{
}

void SetTitleCommand::DoExecute()
{
	m_newValue.swap(m_target);
}

void SetTitleCommand::DoUnexecute()
{
	m_newValue.swap(m_target);
}
