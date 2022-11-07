#pragma once

#include "Menu.h"
#include "../Document/HTMLDocument.h"

class Editor
{
public:
	Editor(std::istream&, std::ostream&);

	void StartEditing();

//TODO: сделать приватными


//TODO: заменить название документ возможно не должен уметь сам себя сохранять; вохможно поможет паттерн visitor или builder
//TODO: запретить изменять параграф; сделать так, чтобы сам парагрфа записывал себя в историю
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

	void HandleInputReadFail(const std::string&) const;

private:
	Menu m_menu;
	HTMLDocument m_document;

	std::istream& m_input;
	std::ostream& m_output;
};
