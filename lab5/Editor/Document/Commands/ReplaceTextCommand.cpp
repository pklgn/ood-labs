#include "../../pch.h"
#include "ReplaceTextCommand.h"


ReplaceTextCommand::ReplaceTextCommand(std::shared_ptr<IParagraph>& target, const std::string& newValue)
	: m_target(target)
	, m_replaceValue(newValue)
{
}

void ReplaceTextCommand::DoExecute()
{
	SwapText();
}

void ReplaceTextCommand::DoUnexecute()
{
	SwapText();
}

void ReplaceTextCommand::SwapText()
{
	auto oldValue = m_target->GetText();
	m_target->SetText(m_replaceValue);
	m_replaceValue = oldValue;
}
