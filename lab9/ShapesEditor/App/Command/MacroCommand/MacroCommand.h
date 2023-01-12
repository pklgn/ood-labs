#pragma once
#include <vector>
#include "../AbstractCommand.h"


class MacroCommand : public AbstractCommand
{
public:
	void AddCommand(std::unique_ptr<ICommand>&&);

protected:
	void DoExecute() final;
	void DoUnexecute() final;

private:
	std::vector<ICommandPtr> m_commands;
};
