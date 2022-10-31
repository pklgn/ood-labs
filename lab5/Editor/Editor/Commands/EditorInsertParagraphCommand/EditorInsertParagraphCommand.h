#pragma once
#include "../../../Command/ICommand.h"
#include "../../../Document/HTMLDocument.h"

class EditorInsertParagraphCommand : public ICommand
{
public:
	EditorInsertParagraphCommand(std::istream& input, HTMLDocument& document);

	void Execute() override;

	void Unexecute() override
	{
	}

private:
	HTMLDocument& m_document;
	std::istream& m_input;
};
