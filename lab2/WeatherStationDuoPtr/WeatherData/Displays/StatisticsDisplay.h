#pragma once

#include "../WeatherData.h"
#include "Display.h"
#include "StatisticsDisplayComponent.h"

class StatisticsDisplay : public Display
{
public:
	StatisticsDisplay(std::ostream&, ObservablePtrType, ObservablePtrType);

private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override;

	StatisticsDisplayComponent m_temprature;
	StatisticsDisplayComponent m_humidity;
	StatisticsDisplayComponent m_pressure;
};