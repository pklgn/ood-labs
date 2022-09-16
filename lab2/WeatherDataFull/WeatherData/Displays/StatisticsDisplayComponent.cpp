#include "StatisticsDisplayComponent.h"

StatisticsDisplayComponent::StatisticsDisplayComponent(std::string& name): m_componentName(name)
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

	std::cout << "Max " << m_componentName << " " << m_max << std::endl;
	std::cout << "Min " << m_componentName << " " << m_min << std::endl;
	std::cout << "Average " << (m_countAcc > 0 ? m_acc / m_countAcc : 0) << std::endl;
	std::cout << "----------------" << std::endl;
}