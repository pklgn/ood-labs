#pragma once

#include "../../pch.h"
#include "../WeatherData.h"
#include "../../Dependents/Dependents.hpp"

enum class ComponentType
{
	TEMPRATURE,
	HUMIDITY,
	PRESSURE,
	WIND_SPEED,
	WIND_ANGLE,
};

class StatisticsDisplayComponent
{
public:
	~StatisticsDisplayComponent() = default;

	virtual void UpdateData(double data);
	void PrintData() const;
	StatisticsDisplayComponent(const ComponentType&, std::ostream&);

protected:
	std::ostream& m_output;
	ComponentType m_componentType;

	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;

	virtual double GetAverageValue() const;
};