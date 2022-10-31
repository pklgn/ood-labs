#include "../../../pch.h"
#include "MenuExitCommand.h"

MenuExitCommand::MenuExitCommand(Menu& menu)
	: m_menu(menu)
{
}

void MenuExitCommand::Execute()
{
	m_menu.Exit();
}
