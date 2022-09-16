#pragma once

#include "../../pch.h"
#include "../WeatherData.h"
#include "../../Dependents/Dependents.hpp"

class StatisticsDisplayComponent
{
public:
	void Update(double data);
	StatisticsDisplayComponent(std::string& name);

private:

	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;

	std::string m_componentName;
};