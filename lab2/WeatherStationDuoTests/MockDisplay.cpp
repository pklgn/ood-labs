#include "MockDisplay.h"

MockDisplay::MockDisplay(std::ostream& output, const std::string& mockInfo)
	: Display(output)
	, m_mockInfo(mockInfo)
{
}

void MockDisplay::Update(SWeatherInfo const& data)
{
	m_output << m_mockInfo;
}
