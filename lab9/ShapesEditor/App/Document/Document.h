#pragma once
#include "../../Model/PictureDraft/PictureDraft.h"
#include "../History/CommandsHistory.h"

class Document
{
public:
	Document();

	void Run();

private:
	void InitEditWindow();

	std::shared_ptr<PictureDraft> m_pictureDraft;
	std::shared_ptr<CommandsHistory> m_commandsHistory;
};