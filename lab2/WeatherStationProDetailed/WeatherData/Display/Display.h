#pragma once

#include "../WeatherData.h"

class Display : public Subscriber<WeatherEvent>
{
public:
	Display(std::ostream&);

protected:
	std::ostream& m_output;

	/* ����� Update ������ ����������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(std::function<void()>& handler) override;
};
