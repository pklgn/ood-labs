#include <iostream>
#include "IncrementCount.h"

void IncrementCount::Increase()
{
	++m_count;
}

count_type IncrementCount::GetCount()
{
	return m_count;
}