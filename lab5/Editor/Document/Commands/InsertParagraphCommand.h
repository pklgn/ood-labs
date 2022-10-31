#pragma once

#include "../../Document/HTMLDocument.h"
#include "../../Command/AbstractCommand.h"

class InsertParagraphCommand : public AbstractCommand
{
public:
	InsertParagraphCommand(std::vector<DocumentItem>& items, const std::shared_ptr<IParagraph>& paragraphPtr, size_t position);

protected:
	void DoExecute() override;

	void DoUnexecute() override;

private:
	std::vector<DocumentItem>& m_items;
	std::shared_ptr<IParagraph> m_paragraphPtr;
	size_t m_position;
};