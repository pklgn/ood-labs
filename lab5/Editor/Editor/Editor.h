#pragma once

#include "Menu.h"
#include "../Document/HTMLDocument.h"

class Editor
{
public:
	Editor();

	void StartEditing();

private:
	Menu m_menu;
	HTMLDocument m_document;
};