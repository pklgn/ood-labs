#include "../../pch.h"
#include "ListDocumentItemsCommand.h"

ListDocumentItemsCommand::ListDocumentItemsCommand(std::vector<DocumentItem>& items, std::ostream& output)
	: m_items(items)
	, m_output(output)
{
}

void ListDocumentItemsCommand::DoExecute()
{
	size_t itemCounter;
	for (auto& item : m_items)
	{
		auto imagePtr = item.GetImage();
		auto paragraphPtr = item.GetParagraph();
		if (imagePtr != nullptr)
		{
			m_output << itemCounter++ << ". "
					 << "Image: "
					 << imagePtr->GetWidth() << " "
					 << imagePtr->GetHeight() << " "
					 << imagePtr->GetPath() << std::endl;
		}
		else if (paragraphPtr != nullptr)
		{
			m_output << itemCounter++ << ". "
					 << "Paragraph: "
					 << paragraphPtr->GetText() << std::endl;
		}
	}
}
