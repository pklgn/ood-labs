#include "../../pch.h"
#include "Display.h"
#include "Tools/AngleTransform.h"

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::Update(const std::function<void()>& handler)
{
	handler();
	m_output << "------------------" << std::endl;
}