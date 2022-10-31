#pragma once

#include "../../../Document/HTMLDocument.h"
#include "../../../Command/ICommand.h"

class EditorSetTitleCommand : public ICommand
{
public:
	EditorSetTitleCommand(std::istream& input, HTMLDocument& document);
	
	void Execute() override;

	void Unexecute() override
	{
	}

private:
	HTMLDocument& m_document;
	std::istream& m_input;
};