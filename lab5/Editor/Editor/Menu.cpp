#include "../pch.h"
#include "Menu.h"

Menu::Menu(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void Menu::AddItem(const std::string& shortcut, const std::string& description, const Command& command)
{
	m_items.emplace_back(shortcut, description, command);
}

void Menu::Run()
{
	std::string command;
	while ((m_output << ">")
		&& getline(m_input, command)
		&& ExecuteCommand(command))
	{
	}
}

void Menu::ShowInstructions() const
{
	m_output << "Commands list:\n";
	for (auto& item : m_items)
	{
		m_output << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

void Menu::Exit()
{
	m_exit = true;
}

bool Menu::ExecuteCommand(const std::string& command)
{
	m_exit = false;
	auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == command;
	});

	if (it != m_items.end())
	{
		try
		{
			it->command();
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
		}
	}
	else
	{
		m_output << "Unknown command\n";
	}
	
	return !m_exit;
}
