#include "../../../pch.h"
#include "MenuHelpCommand.h"

MenuHelpCommand::MenuHelpCommand(const Menu& menu)
	: m_menu(menu)
{
}

void MenuHelpCommand::Execute()
{
	m_menu.ShowInstructions();
}
