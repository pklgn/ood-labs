#pragma once

#include "../WeatherData.h"
#include "StatisticsDisplayComponent.h"
#include "StatisticsDisplayAngleComponent.h"

class StatisticsDisplay : public IObserver<SWeatherInfo>
{
public:
	StatisticsDisplay(std::ostream&);

protected:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data) override;

	StatisticsDisplayComponent m_temprature;
	StatisticsDisplayComponent m_humidity;
	StatisticsDisplayComponent m_pressure;
	StatisticsDisplayComponent m_windSpeed;
	StatisticsDisplayAngleComponent m_windAngle;

};