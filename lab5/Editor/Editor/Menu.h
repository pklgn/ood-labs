#pragma once
#include <string>
#include <vector>

#include "../Command/ICommand.h"

class Menu
{
public:
	void AddItem(const std::string& shortcut, const std::string& description, ICommandPtr&& command);

	void Run();

	void ShowInstructions() const;

	void Exit();

private:
	bool ExecuteCommand(const std::string& command);

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, ICommandPtr&& command)
			: shortcut(shortcut)
			, description(description)
			, command(std::move(command))
		{
		}

		std::string shortcut;
		std::string description;
		ICommandPtr command;
	};
	std::vector<Item> m_items;
	bool m_exit = false;
};