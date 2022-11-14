#pragma once

#include "../pch.h"

template <typename T>
class IObserver;

template <typename T>
class IObservable;

template <class T>
struct ObserverWithEventAction
{
	ObserverWithEventAction(IObserver<T>* ptr, const T& event, const std::function<void()>& action)
		: m_ptr(ptr)
		, m_event(event)
		, m_action(action)
	{
	}

	IObserver<T>* m_ptr;
	T m_event;
	std::function<void()> m_action;
};


template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;

	virtual void AddObserver(IObserver<T>* observerPtr, const T& event, const std::function<void()>& handler, size_t priority = 0) = 0;

	virtual void RemoveObserver(IObserver<T>* observerPtr, const T& event) = 0;

	virtual void OnPublish(const T& event) = 0;
};

/*
Шаблонный интерфейс ISubscriber. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual ~IObserver() = default;
};

template <class T>
class Observable : public IObservable<T>
{
public:
	void AddObserver(IObserver<T>* subscriberPtr, const T& event, const std::function<void()>& handler, size_t priority = 0) override
	{
		RemoveObserver(subscriberPtr, event);
		m_subscribers.emplace(priority, ObserverWithEventAction<T>(subscriberPtr, event, handler));
	}

	void RemoveObserver(IObserver<T>* targetSubscriberPtr, const T& targetEvent) override
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

	void OnPublish(const T& event) override
	{
		for (auto& [_, subscriber] : m_subscribers)
		{
			if (subscriber.m_event == event)
			{
				subscriber.m_action();
			}
		}
	}

private:
	std::multimap<size_t, ObserverWithEventAction<T>> m_subscribers;
};