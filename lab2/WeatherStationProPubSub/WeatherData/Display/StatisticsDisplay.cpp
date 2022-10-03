#include "../../pch.h"
#include "StatisticsDisplay.h"

StatisticsDisplay::StatisticsDisplay(std::ostream& output)
	: m_temprature(ComponentType::TEMPRATURE, output)
{
}

void StatisticsDisplay::Update(const std::function<void()>& handler)
{
	handler();

	std::cout << "Local weather forecast provided by Meteum\n";
}