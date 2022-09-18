#pragma once

#include "../WeatherData.h"
#include "../../Dependents/Dependents.hpp"

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
	void Update(SWeatherInfo const& data) override;
};
