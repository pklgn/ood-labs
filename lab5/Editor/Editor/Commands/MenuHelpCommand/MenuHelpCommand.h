#pragma once

#include "../../Menu.h"
#include "../../../Command/ICommand.h"

class MenuHelpCommand : public ICommand
{
public:
	MenuHelpCommand(const Menu& menu);

	void Execute() override;

	void Unexecute() override
	{
	}

private:
	const Menu& m_menu;
};