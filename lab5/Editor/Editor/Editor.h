#pragma once

#include "Menu.h"
#include "../Document/HTMLDocument.h"

class Editor
{
public:
	Editor(std::istream&, std::ostream&);

	void StartEditing();

protected:
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

	void Exit();

	size_t ReadPosition();

private:
	Menu m_menu;
	HTMLDocument m_document;

	std::istream& m_input;
	std::ostream& m_output;
};
