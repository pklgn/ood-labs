#pragma once

#include "../../pch.h"
#include "../WeatherData.h"
#include "../../Dependents/Dependents.hpp"

enum class ComponentType
{
	TEMPRATURE,
	HUMIDITY,
	PRESSURE,
};

class StatisticsDisplayComponent
{
public:
	void Update(double data);
	StatisticsDisplayComponent(const ComponentType&, std::ostream&);

private:
	std::ostream& m_output;
	ComponentType m_componentType;

	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};