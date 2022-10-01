#pragma once

#include "../pch.h"

template <typename T>
class IObservable;

class IEvent
{
public:
	virtual unsigned int GetId() = 0;
};

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual ~IObserver() = default;

	template <typename UpdateDataType>
	virtual void Update(T const& data, std::function<T> const& handler) = 0;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;

	template <typename ReturnType>
	virtual void RegisterObserver(IObserver const& observer, const IEvent& event, const std::function<ReturnType()>& handler) = 0;
	virtual void RemoveObserver(const IEvent& event, IObserver const& observer) = 0;
	virtual void NotifyObservers(const IEvent& event) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;
	using Subcriber = std::pair<IObserver*, std::function*>;

	void RegisterObserver(IObserver const& observer, const IEvent& event, const std::function<ReturnType()>& handler) override
	{
		RemoveObserver(observer, event);
		Subcriber subscriber = std::make_pair(&observer, &handler);
		m_subsribers.emplace(event, subscriber);
	}

	void RemoveObserver(IObserver const& observer, const IEvent& event) override
	{
		auto search = std::find_if(m_subsribers.begin(), m_subsribers.end(),
			[&](auto eventSubscriberPair) {
				auto [observerPtr, handlerPtr] = eventSubscriberPair.second;
				return observerPtr == &observer;
			});

		if (search != m_observers.end())
		{
			m_observers.erase(search);
		}
	}

	void NotifyObservers(const IEvent& event) override
	{
		T data = GetChangedData();
		
		auto iter = m_subsribers.begin();
		while (iter != m_subsribers.end())
		{
			auto [subscriberEvent, subscriber] = *iter;
			auto [observerPtr, handlerPtr] = subscriber;
			++iter;
			if (event.GetId() == subscriberEvent.GetId())
			{
				observerPtr->handlerPtr();
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::multimap<IEvent, Subcriber> m_subsribers;
};
