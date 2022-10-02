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

template <class T>
struct SubscriberWithEventAction
{
	SubscriberWithEventAction(ISubscriber<T>* ptr, const T& event, const std::function<void()>& action)
		: m_ptr(ptr)
		, m_event(event)
		, m_action(action)
	{
	}

	ISubscriber<T>* m_ptr;
	const T m_event;
	const std::function<void()>& m_action;
};


template <typename T>
class IBroker
{
public:
	virtual ~IBroker() = default;

	virtual void AddSubscriber(ISubscriber<T>* subscriberPtr, const T& event, std::function<void()>& handler, size_t priority = 0) = 0;

	virtual void RemoveSubscriber(ISubscriber<T>* subscriberPtr, const T& event) = 0;

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

	virtual void SubscribeToBroker(IBroker<T>* broker, const T& event, std::function<void()>& handler, size_t priority = 0) = 0;

	virtual void UnubscribeFromBroker(IBroker<T>* ptr, const T& event) = 0;

	virtual void Update(const std::function<void()>&) = 0;
};

template <class T>
class Subscriber : public ISubscriber<T>
{
public:
	void SubscribeToBroker(IBroker<T>* broker, const T& event, std::function<void()>& handler, size_t priority = 0) override
	{
		m_events.insert(event);
		broker->AddSubscriber(this, event, handler, priority);
	}

	void UnubscribeFromBroker(IBroker<T>* broker, const T& event) override
	{
		m_events.erase(event);
		broker->RemoveSubscriber(this, event);
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

template <class T>
class Broker : public IBroker<T>
{
public:
	void AddSubscriber(ISubscriber<T>* subscriberPtr, const T& event, std::function<void()>& handler, size_t priority = 0) override
	{
		RemoveSubscriber(subscriberPtr, event);
		SubscriberWithEventAction<T> s = SubscriberWithEventAction<T>(subscriberPtr, event, handler);
		m_subscribers.emplace(priority, s);
	}

	void RemoveSubscriber(ISubscriber<T>* targetSubscriberPtr, const T& targetEvent) override
	{
		auto search = std::find_if(m_subscribers.begin(), m_subscribers.end(),
			[&](auto& prioritySubscriberPair) {
				return prioritySubscriberPair.second.m_ptr == targetSubscriberPtr &&
					prioritySubscriberPair.second.m_event == targetEvent;
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
		for (auto [_, subscriber] : m_subscribers)
		{
			if (subscriber.m_event == event)
			{
				subscriber.m_ptr->Update(subscriber.m_action);
			}
		}
	}

private:
	//IPublisher<T>* m_publisherPtr;

	std::multimap<size_t, SubscriberWithEventAction<T>&> m_subscribers;
};