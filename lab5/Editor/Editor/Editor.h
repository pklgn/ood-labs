#pragma once

#include "Menu.h"
#include "../Document/HTMLDocument.h"

class Editor
{
public:
	Editor(std::istream&, std::ostream&);

	void StartEditing();

	void InsertParagraph();

	void InsertImage();

	void SetTitle();

	void List() const;

	void ReplaceText();

	void ResizeImage();

	void DeleteItem();

	void Help() const;

	void Undo();

	void Redo();

	void Save() const;


protected:
	size_t ReadInsertPosition();

private:
	Menu m_menu;
	HTMLDocument m_document;

	std::istream& m_input;
	std::ostream& m_output;
};
