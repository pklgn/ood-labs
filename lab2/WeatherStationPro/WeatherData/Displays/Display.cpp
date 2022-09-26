#include "../../pch.h"
#include "Display.h"
#include "Tools/AngleTransform.h"

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::Update(SWeatherInfo const& data)
{
	m_output << "Current Temprature: " << data.temperature << std::endl;
	m_output << "Current Humidity: " << data.humidity << std::endl;
	m_output << "Current Pressure: " << data.pressure << std::endl;
	m_output << "Current Wind Speed: " << data.wind.speed << std::endl;
	m_output << "Current Wind Angle: " << GetPositiveAngle(data.wind.angle) << std::endl;
	m_output << "------------------" << std::endl;
}