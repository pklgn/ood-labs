#pragma once

#include "../../Command/AbstractCommand.h"
#include "../../Document/HTMLDocument.h"

class InsertImageCommand : public AbstractCommand
{
public:
	InsertImageCommand(std::vector<DocumentItem>& items, const std::shared_ptr<IImage>& imagePtr, size_t position, const Path& path);

	~InsertImageCommand();

protected:
	void DoExecute() override;

	void DoUnexecute() override;

private:
	std::vector<DocumentItem>& m_items;
	std::shared_ptr<IImage> m_imagePtr;
	size_t m_position;
	Path m_path;
};