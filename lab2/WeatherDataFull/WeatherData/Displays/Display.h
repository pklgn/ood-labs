#pragma once

#include "../WeatherData.h"
#include "../../Dependents/Dependents.hpp"

class Display : public IObserver<SWeatherInfo>
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
