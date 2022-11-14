#include "../../pch.h"
#include "StatisticsDisplay.h"

StatisticsDisplay::StatisticsDisplay(std::ostream& output)
	: m_temprature(ComponentType::TEMPRATURE, output)
{
}