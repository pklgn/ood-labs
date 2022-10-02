#pragma once

#include "../WeatherData.h"

class Display : public ISubscriber<WeatherEvent>
{
public:
	Display(std::ostream&);

protected:
	std::ostream& m_output;

	/* ����� Update ������ ����������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(const std::function<void()>& handler) override;
};
