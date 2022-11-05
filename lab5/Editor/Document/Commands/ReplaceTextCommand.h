#pragma once

#include "../../Command/AbstractCommand.h"
#include "../../Document/HTMLDocument.h"

class ReplaceTextCommand : public AbstractCommand
{
public:
	ReplaceTextCommand(std::shared_ptr<IParagraph>& paragraph, const std::string& newValue);

protected:
	void DoExecute() override;

	void DoUnexecute() override;

	void SwapText();

private:
	std::shared_ptr<IParagraph> m_target;
	std::string m_replaceValue;
};