#include "../../pch.h"
#include "StatisticsDisplay.h"

StatisticsDisplay::StatisticsDisplay(std::ostream& output)
	: m_temprature(ComponentType::TEMPRATURE, output)
	, m_humidity(ComponentType::HUMIDITY, output)
	, m_pressure(ComponentType::PRESSURE, output)
{
}

void StatisticsDisplay::Update(SWeatherInfo const& data, Observable<SWeatherInfo>& observable)
{
	m_temprature.Update(data.temperature);
	m_humidity.Update(data.humidity);
	m_pressure.Update(data.pressure);
}