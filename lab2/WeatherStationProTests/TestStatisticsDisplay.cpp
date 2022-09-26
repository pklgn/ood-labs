#include "TestStatisticsDisplay.h"

TestStatisticsDisplay::TestStatisticsDisplay(std::ostream& output)
	: StatisticsDisplay(output)
{
}

void TestStatisticsDisplay::Update(SWeatherInfo const& data)
{
	m_windAngle.UpdateData(data.wind.angle);

	m_windAngle.PrintData();
}