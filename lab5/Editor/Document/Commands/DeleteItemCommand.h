#pragma once

#include "../../Command/AbstractCommand.h"
#include "../../Document/HTMLDocument.h"

class DeleteItemCommand : public AbstractCommand
{
public:
	DeleteItemCommand(std::vector<DocumentItem>& items, size_t position);

	~DeleteItemCommand();

protected:
	void DoExecute() override;

	void DoUnexecute() override;

private:
	std::vector<DocumentItem>& m_items;
	size_t m_position;
	DocumentItem m_documentItem;
};
