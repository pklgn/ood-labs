#pragma once

#include "../../../Command/ICommand.h"
#include "../../../Document/HTMLDocument.h"

class EditorInsertImageCommand : public ICommand
{
public:
	EditorInsertImageCommand(std::istream& input, HTMLDocument& document);

	void Execute() override;

	void Unexecute() override
	{
	}

private:
	HTMLDocument& m_document;
	std::istream& m_input;
};