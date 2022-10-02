#include "../../pch.h"
#include "StatisticsDisplay.h"

StatisticsDisplay::StatisticsDisplay(std::ostream& output)
	: m_temprature(ComponentType::TEMPRATURE, output)
	, m_humidity(ComponentType::HUMIDITY, output)
	, m_pressure(ComponentType::PRESSURE, output)
	, m_windSpeed(ComponentType::WIND_SPEED, output)
	, m_windAngle(ComponentType::WIND_ANGLE, output)
{
}

void StatisticsDisplay::Update(const std::function<void()>& handler)
{
	//m_temprature.UpdateData(data.temperature);
	//m_humidity.UpdateData(data.humidity);
	//m_pressure.UpdateData(data.pressure);
	//m_windSpeed.UpdateData(data.wind.speed);
	//m_windAngle.UpdateData(data.wind.angle);


	//m_temprature.PrintData();
	//m_humidity.PrintData();
	//m_pressure.PrintData();
	//m_windSpeed.PrintData();
	//m_windAngle.PrintData();
}