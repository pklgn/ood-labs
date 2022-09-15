#pragma once

#include "../WeatherData.h"
#include "../../Dependents/Dependents.hpp"


class Display : public IObserver<SWeatherInfo>

{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data) override;
};