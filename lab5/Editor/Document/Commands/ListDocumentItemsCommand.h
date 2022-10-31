#pragma once

#include "../../Document/HTMLDocument.h"
#include "../../Command/AbstractCommand.h"

class ListDocumentItemsCommand : public AbstractCommand
{
public:
	ListDocumentItemsCommand(std::vector<DocumentItem>&, std::ostream&);

protected :
	void DoExecute() override;

	void DoUnexecute() override
	{
	}

private:
	std::vector<DocumentItem>& m_items;
	std::ostream& m_output;
};
//TODO: убрать команду