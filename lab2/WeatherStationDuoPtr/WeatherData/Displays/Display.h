#pragma once

#include "../WeatherData.h"

class Display : public IObserver<SWeatherInfo>
{
public:
	using ObservablePtrType = IObservable<SWeatherInfo>*;

	virtual ~Display() = default;

	Display(std::ostream&, ObservablePtrType, ObservablePtrType);

protected:
	std::ostream& m_output;

	IObservable<SWeatherInfo>* m_weatherObservableInside;
	IObservable<SWeatherInfo>* m_weatherObservableOutside;

	/* ����� Update ������ ����������, ����� ���������� ����������� ��� ������ ��������
	������ Observable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const&) override;

	void PrintLocation(IObservable<SWeatherInfo> const&);
};
