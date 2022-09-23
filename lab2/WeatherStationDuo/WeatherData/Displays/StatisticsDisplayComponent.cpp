#include "StatisticsDisplayComponent.h"

StatisticsDisplayComponent::StatisticsDisplayComponent(const ComponentType& type, std::ostream& output)
	: m_componentType(type)
	, m_output(output)
{
}

void StatisticsDisplayComponent::Update(double value)
{
	if (m_min > value)
	{
		m_min = value;
	}
	if (m_max < value)
	{
		m_max = value;
	}
	
	m_acc += value;
	++m_countAcc;

	m_output << std::setprecision(2) << std::fixed;
	m_output << ComponentTypeToString() << ":" << std::endl;
	m_output << "Max " << m_max << std::endl;
	m_output << "Min " << m_min << std::endl;
	m_output << "Avg " << (m_countAcc > 0 ? m_acc / m_countAcc : 0) << std::endl;
	m_output << "----------------" << std::endl;
	m_output << std::setprecision(-1) << std::defaultfloat;
}

std::string StatisticsDisplayComponent::ComponentTypeToString()
{
	switch (m_componentType)
	{
	case ComponentType::TEMPRATURE:
		return "TEMPRATURE";
	case ComponentType::HUMIDITY:
		return "HUMIDITY";
	case ComponentType::PRESSURE:
		return "PRESSURE";
	default:
		return "";
	}
}