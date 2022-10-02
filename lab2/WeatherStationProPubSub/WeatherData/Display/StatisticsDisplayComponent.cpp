#include "StatisticsDisplayComponent.h"

std::string ComponentTypeToString(ComponentType componentType)
{
	switch (componentType)
	{
	case ComponentType::TEMPRATURE:
		return "TEMPRATURE";
	case ComponentType::HUMIDITY:
		return "HUMIDITY";
	case ComponentType::PRESSURE:
		return "PRESSURE";
	case ComponentType::WIND_SPEED:
		return "WIND SPEED";
	case ComponentType::WIND_ANGLE:
		return "WIND ANGLE";
	default:
		return "";
	}
}

StatisticsDisplayComponent::StatisticsDisplayComponent(const ComponentType& type, std::ostream& output)
	: m_componentType(type)
	, m_output(output)
{
}

void StatisticsDisplayComponent::UpdateData(double value)
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
}

void StatisticsDisplayComponent::PrintData() const
{
	m_output << std::setprecision(2) << std::fixed;
	m_output << ComponentTypeToString(m_componentType) << " statistics:" << std::endl;
	m_output << "Max " << m_max << std::endl;
	m_output << "Min " << m_min << std::endl;
	m_output << "Avg " << GetAverageValue() << std::endl;
	m_output << "----------------" << std::endl;
	m_output << std::setprecision(-1) << std::defaultfloat;
}

double StatisticsDisplayComponent::GetAverageValue() const
{
	return m_countAcc > 0 ? m_acc / m_countAcc : 0;
}
