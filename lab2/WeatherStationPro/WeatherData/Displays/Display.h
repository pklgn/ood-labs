#pragma once

#include "../WeatherData.h"

class Display : public IObserver<SWeatherInfo>
{
public:
	Display(std::ostream&);

protected:
	std::ostream& m_output;

	/* ����� Update ������ ����������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data) override;

	std::string GetLocationToString(Location);
};
