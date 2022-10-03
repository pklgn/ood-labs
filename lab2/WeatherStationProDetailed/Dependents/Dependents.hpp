#pragma once

#include "../pch.h"

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
class ISubscriber;

template <typename T>
class IPublisher;

template <typename T>
class IBroker;

template <typename T>
struct SubscriberWithEventAction
{
	ISubscriber<T>* ptr;
	T& event;
	std::function<void()>& action;
};


template <typename T>
class IBroker
{
public:
	virtual void AddSubscriber(ISubscriber<T>* subscriberPtr, T& event) = 0;

	virtual void RemoveSubscriber(ISubscriber<T>* subscriberPtr, T& event) = 0;

	virtual void RegisterToPublisher(IPublisher<T>* publisherPtr) = 0;

	virtual void OnPublish(const T& event) = 0;
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
	virtual ~ISubscriber() = default;

	virtual void SubscribeToBroker(IBroker<T>* ptr, T event) = 0;

	virtual void UnubscribeFromBroker(IBroker<T>* ptr, T event) = 0;

	virtual void Update(std::function<void()>&) = 0;
};

template <typename T>
class Subscriber : public ISubscriber<T>
{
public:
	void SubscribeToBroker(IBroker<T>* broker, T event) override
	{
		m_events.insert(event);
		broker->AddSubscriber(static_cast<ISubscriber<T>*>(this), event);
	}

	void UnubscribeFromBroker(IBroker<T>* broker, T event) override
	{
		m_events.erase(event);
		broker->RemoveSubscriber(static_cast<ISubscriber<T>*>(this), event);
	}

private:
	std::set<T> m_events;
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

	virtual void PublishToBroker(const T& event) = 0;

	virtual void RemoveBroker(IBroker<T>* pBroker) = 0;
};

template <class T>
class Publisher : public IPublisher<T>
{

public:
	virtual ~Publisher() = default;

	void RegisterBroker(IBroker<T>* pBroker) override
	{
		m_brokerPtr = pBroker;
	}

	void PublishToBroker(const T& event) override
	{
		if (m_brokerPtr)
		{
			m_brokerPtr->OnPublish(event);
		}
	}

	void RemoveBroker(IBroker<T>* pBroker) override
	{
		m_brokerPtr = nullptr;
	}

protected:
	IBroker<T>* m_brokerPtr;
};

template <typename T>
class Broker : public IBroker<T>
{
public:
	~Broker() = default;

	void AddSubscriber(ISubscriber<T>* subscriberPtr, T& event) override
	{
		RemoveSubscriber(subscriberPtr, event);
		m_subscribers.emplace(event, std::make_pair(subscriberPtr, event));
	}

	void RemoveSubscriber(ISubscriber<T>* targetSubscriberPtr, T& targetEvent) override
	{
		auto search = std::find_if(m_subscribers.begin(), m_subscribers.end(),
			[&](auto prioritySubscriberPair) {
				auto& [subscriberPtr, event] = prioritySubscriberPair;
				return subscriberPtr == targetSubscriberPtr && event == targetEvent;
			});

		if (search != m_subscribers.end())
		{
			m_subscribers.erase(search);
		}
	}

	void RegisterToPublisher(IPublisher<T>* publisher) override
	{
		publisher->RegisterBroker(this);
	}

	void OnPublish(const T& event) override
	{
		for (auto& [_, subscriber] : m_subscribers)
		{
			if (subscriber.event == event)
			{
				subscriber.ptr->Update(subscriber.action);
			}
		}
	}

private:
	IPublisher<T>* m_publisherPtr;

	std::multimap<size_t, SubscriberWithEventAction<T>> m_subscribers;
};