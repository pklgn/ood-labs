#pragma once

#include "../WeatherData.h"
#include "StatisticsDisplayComponent.h"

class StatisticsDisplay : public Observer<SWeatherInfo>
{
public:
	StatisticsDisplay(std::ostream&);

private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data) override;

	StatisticsDisplayComponent m_temprature;
	StatisticsDisplayComponent m_humidity;
	StatisticsDisplayComponent m_pressure;
};