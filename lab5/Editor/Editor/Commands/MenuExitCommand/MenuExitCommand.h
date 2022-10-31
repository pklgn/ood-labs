#pragma once

#include "../../Menu.h"
#include "../../../Command/ICommand.h"

class MenuExitCommand : public ICommand
{
public:
	MenuExitCommand(Menu& menu);

	void Execute() override;

	void Unexecute() override
	{
	}

private:
	Menu& m_menu;
};