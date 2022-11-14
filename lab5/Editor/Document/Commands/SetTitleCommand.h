#pragma once

#include "../../Command/AbstractCommand.h"
#include "../../Document/HTMLDocument.h"

class SetTitleCommand : public AbstractCommand
{
public:
	SetTitleCommand(std::string& target, const std::string& newValue);

protected:
	void DoExecute() override;

	void DoUnexecute() override;

private:
	std::string& m_target;
	std::string m_newValue;
};