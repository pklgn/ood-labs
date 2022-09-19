#pragma once

#include "../WeatherData.h"

class Display : public Observer<SWeatherInfo>
{
public:
	Display(std::ostream&);

private:
	std::ostream& m_output;
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override;
};
