#include "../../pch.h"
#include "StatisticsDisplay.h"

void StatisticsDisplay::Update(SWeatherInfo const& data)
{
	m_temprature.Update(data.temperature);
	m_humidity.Update(data.humidity);
	m_pressure.Update(data.pressure);
}