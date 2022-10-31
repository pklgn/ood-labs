#include "../pch.h"
#include "Editor.h"
#include "Commands/EditorInsertParagraphCommand/EditorInsertParagraphCommand.h"
#include "Commands/EditorInsertImageCommand/EditorInsertImageCommand.h"
#include "Commands/EditorSetTitleCommand/EditorSetTitleCommand.h"
#include "../Document/Commands/ListDocumentItemsCommand.h"


Editor::Editor()
{
	m_menu.AddItem("insert_paragraph",
		"Inserting specified paragraph with a given position",
		std::make_unique<EditorInsertParagraphCommand>(std::cin, m_document));

	m_menu.AddItem("insert_image",
		"Inserting specified image with a given position",
		std::make_unique<EditorInsertImageCommand>(std::cin, m_document));

	m_menu.AddItem("set_title",
		"Set a new title for the document",
		std::make_unique<EditorSetTitleCommand>(std::cin, m_document));

	m_menu.AddItem("list",
		"Show document items list",
		std::make_unique<ListDocumentItemsCommand>(m_document.GetDocumentItems(), std::cout));


}

//TODO: убрать команды и заменить на std::function(void)

void Editor::StartEditing()
{
	m_menu.ShowInstructions();

	m_menu.Run();
}
