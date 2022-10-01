#define _USE_MATH_DEFINES
#include <math.h>
#include "Tools/AngleTransform.h"
#include "StatisticsDisplayAngleComponent.h"

void StatisticsDisplayAngleComponent::UpdateData(double angle)
{
	double unsignedAngle = GetPositiveAngle(angle);
	if (m_min > unsignedAngle)
	{
		m_min = unsignedAngle;
	}
	if (m_max < unsignedAngle)
	{
		m_max = unsignedAngle;
	}

	m_x += cos(angle * M_PI / 180);
	m_y += sin(angle * M_PI / 180);
	m_countAcc++;

	double signResult = atan2(m_y, m_x) * 180 / M_PI;

	m_acc = GetPositiveAngle(signResult);
}

double StatisticsDisplayAngleComponent::GetAverageValue() const
{
	return m_acc;
}

StatisticsDisplayAngleComponent::StatisticsDisplayAngleComponent(const ComponentType& type, std::ostream& output)
	: StatisticsDisplayComponent(type, output)
{

}

// TODO: сделать независимым