#pragma once

#include "../WeatherData.h"

class Display : public Subscriber
{
public:
	Display(std::ostream&);

protected:
	std::ostream& m_output;

	/* ����� Update ������ ����������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(double newValue, WeatherEvent) override;
};
