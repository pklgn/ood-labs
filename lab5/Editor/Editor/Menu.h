#pragma once
#include <string>
#include <vector>
#include <functional>

#include "../Command/ICommand.h"

class Menu
{
public:
	using Command = std::function<void()>;

	Menu(std::istream& input, std::ostream& output);

	void AddItem(const std::string& shortcut, const std::string& description, const Command& command);

	void Run();

	void ShowInstructions() const;

	void Exit();

private:
	bool ExecuteCommand(const std::string& command);

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{
		}

		std::string shortcut;
		std::string description;
		Command command;
	};

	std::vector<Item> m_items;
	bool m_exit = false;

	std::istream& m_input;
	std::ostream& m_output;
};