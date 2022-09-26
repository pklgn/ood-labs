#pragma once

#include "../pch.h"

template <typename T>
class ISubscriber;

template <typename T>
class IPublisher;

template <typename T>
class IBroker;

enum class WeatherEvent
{
	TEMPRATURE,
	PRESSURE,
	HUMIDITY,
	WIND_SPEED,
	WIND_ANGLE,
	NO_EVENT,
};


template <typename T>
class IBroker
{
public:
	virtual void AddSubscriber(ISubscriber<T>* ptr, T event) = 0;

	virtual void RemoveSubscriber(ISubscriber<T>* ptr, T event) = 0;

	virtual void RegisterToPublisher(IPublisher<T>* ptr) = 0;

	virtual void OnPublish(T event, double newData) = 0;
};

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class ISubscriber
{
public:
	virtual void SubscribeToBroker(IBroker<T>* ptr, T event) = 0;

	virtual void UnubscribeFromBroker(IBroker<T>* ptr, T event) = 0;

	virtual void Update(double newValue, WeatherEvent) = 0;
};

class Subscriber : public ISubscriber<WeatherEvent>
{
public:
	virtual ~Subscriber() = default;

	void SubscribeToBroker(IBroker<WeatherEvent>* broker, WeatherEvent event) override
	{
		m_events.insert(event);
		broker->AddSubscriber(this, event);
	}

	void UnubscribeFromBroker(IBroker<WeatherEvent>* broker, WeatherEvent event) override
	{
		m_events.erase(event);
		broker->RemoveSubscriber(this, event);
	}

private:
	std::set<WeatherEvent> m_events;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IPublisher
{
public:
	virtual ~IPublisher() = default;

	virtual void RegisterBroker(IBroker<T>* pBroker) = 0;

	virtual void PublishToBroker(T event, double newData) = 0;

	virtual void RemoveBroker(IBroker<WeatherEvent>* pBroker) = 0;
};

template <class T>
class Publisher : public IPublisher<WeatherEvent>
{

public:
	virtual ~Publisher() = default;

	void RegisterBroker(IBroker<WeatherEvent>* pBroker) override
	{
		m_brokerPtr = pBroker;
	}

	void PublishToBroker(WeatherEvent event, double newData) override
	{
		if (m_brokerPtr)
		{
			m_brokerPtr->OnPublish(event, newData);
		}
	}

	void RemoveBroker(IBroker<WeatherEvent>* pBroker) override
	{
		m_brokerPtr = nullptr;
	}

protected:
	virtual T GetChangedData() const = 0;

	IBroker<WeatherEvent>* m_brokerPtr;
};

class Broker : public IBroker<WeatherEvent>
{
public:
	~Broker() = default;

	void AddSubscriber(ISubscriber<WeatherEvent>* ptr, WeatherEvent event) override
	{
		switch (event)
		{
		case WeatherEvent::TEMPRATURE:
			m_tempratureSubs.insert(ptr);
			break;
		case WeatherEvent::HUMIDITY:
			m_humiditySubs.insert(ptr);
			break;
		case WeatherEvent::PRESSURE:
			m_pressureSubs.insert(ptr);
			break;
		case WeatherEvent::WIND_SPEED:
			m_windSpeedSubs.insert(ptr);
			break;
		case WeatherEvent::WIND_ANGLE:
			m_windAngleSubs.insert(ptr);
			break;
		}
	}

	void RemoveSubscriber(ISubscriber<WeatherEvent>* ptr, WeatherEvent event) override
	{
		switch (event)
		{
		case WeatherEvent::TEMPRATURE:
			m_tempratureSubs.erase(ptr);
			break;
		case WeatherEvent::HUMIDITY:
			m_humiditySubs.erase(ptr);
			break;
		case WeatherEvent::PRESSURE:
			m_pressureSubs.erase(ptr);
			break;
		case WeatherEvent::WIND_SPEED:
			m_windSpeedSubs.erase(ptr);
			break;
		case WeatherEvent::WIND_ANGLE:
			m_windAngleSubs.erase(ptr);
			break;
		}
	}

	void RegisterToPublisher(IPublisher<WeatherEvent>* publisher) override
	{
		publisher->RegisterBroker(this);
	}

	void OnPublish(WeatherEvent event, double newData) override
	{
		switch (event)
		{
		case WeatherEvent::TEMPRATURE:
			OnUpdate(m_tempratureSubs, newData, event);
			break;
		case WeatherEvent::HUMIDITY:
			OnUpdate(m_humiditySubs, newData, event);
			break;
		case WeatherEvent::PRESSURE:
			OnUpdate(m_pressureSubs, newData, event);
			break;
		case WeatherEvent::WIND_SPEED:
			OnUpdate(m_windSpeedSubs, newData, event);
			break;
		case WeatherEvent::WIND_ANGLE:
			OnUpdate(m_windAngleSubs, newData, event);
			break;
		}
	}

private:
	IPublisher<WeatherEvent>* m_publisherPtr;
	std::set<ISubscriber<WeatherEvent>*> m_tempratureSubs;
	std::set<ISubscriber<WeatherEvent>*> m_pressureSubs;
	std::set<ISubscriber<WeatherEvent>*> m_humiditySubs;
	std::set<ISubscriber<WeatherEvent>*> m_windSpeedSubs;
	std::set<ISubscriber<WeatherEvent>*> m_windAngleSubs;

	void OnUpdate(std::set<ISubscriber<WeatherEvent>*> subs, double newData, WeatherEvent event)
	{
		for (auto& sub : subs)
		{
			sub->Update(newData, event);
		}
	}
};