// Console_Editor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../Editor/Editor/Editor.h"

int main()
{
	Editor editor(std::cin, std::cout);

	editor.StartEditing();
}
