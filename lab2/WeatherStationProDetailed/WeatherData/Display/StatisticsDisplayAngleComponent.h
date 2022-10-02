#pragma once

#include "StatisticsDisplayComponent.h"

class StatisticsDisplayAngleComponent : public StatisticsDisplayComponent
{
public:
	StatisticsDisplayAngleComponent(const ComponentType&, std::ostream&);

	void UpdateData(double data) override;

protected:
	double GetAverageValue() const override;

private:
	double m_x = 0;
	double m_y = 0;
};