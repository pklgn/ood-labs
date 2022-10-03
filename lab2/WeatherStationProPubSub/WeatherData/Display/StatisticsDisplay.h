#pragma once

#include "../WeatherData.h"
#include "StatisticsDisplayComponent.h"
#include "StatisticsDisplayAngleComponent.h"

class StatisticsDisplay : public Subscriber<WeatherEvent>
{
public:
	StatisticsDisplay(std::ostream&);

protected:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(const std::function<void()>& handler) override;

	StatisticsDisplayComponent m_temprature;
};