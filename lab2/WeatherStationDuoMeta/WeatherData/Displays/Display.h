#pragma once

#include "../WeatherData.h"

class Display : public IObserver<SWeatherInfo, Location>
{
public:
	Display(std::ostream&);

protected:
	std::ostream& m_output;

	/* ����� Update ������ ����������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data, Location const& metaData) override;
};
