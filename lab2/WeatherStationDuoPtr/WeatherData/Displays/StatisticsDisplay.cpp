#include "../../pch.h"
#include "StatisticsDisplay.h"

StatisticsDisplay::StatisticsDisplay(std::ostream& output, ObservablePtrType weatherInside, ObservablePtrType weatherOutside)
	: Display(output, weatherInside, weatherOutside)
	, m_temprature(ComponentType::TEMPRATURE, output)
	, m_humidity(ComponentType::HUMIDITY, output)
	, m_pressure(ComponentType::PRESSURE, output)
{
}

void StatisticsDisplay::Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable)
{
	PrintLocation(observable);

	m_temprature.UpdateData(data.temperature);
	m_humidity.UpdateData(data.humidity);
	m_pressure.UpdateData(data.pressure);

	m_temprature.PrintData();
	m_humidity.PrintData();
	m_pressure.PrintData();
}