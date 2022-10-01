#pragma once

#include "../pch.h"

template <typename T>
class IPublisher;

class IEvent
{
public:
	virtual unsigned int GetId() const = 0;
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

	virtual void Update(IPublisher<T>& publisher, std::function<void()>& pullHandler) = 0;
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

	virtual void RegisterObserver(ISubscriber<T> & subscriber,  IEvent& event, std::function<void()>& pullHandler) = 0;
	virtual void RemoveObserver(ISubscriber<T> & subscriber,  IEvent* event) = 0;
	virtual void NotifyObservers(IEvent* event) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class Publisher : public IPublisher<T>
{
public:
	using ObserverType = ISubscriber<T>;

	void RegisterObserver(ISubscriber<T> & subscriber, IEvent& event, std::function<void()>& pullHandler) override
	{
		RemoveObserver(subscriber, &event);
		m_subsribers.insert(&event, std::make_pair(&subscriber, pullHandler));
	}

	void RemoveObserver(ISubscriber<T> & subscriber,  IEvent* event) override
	{
		auto search = std::find_if(m_subsribers.begin(), m_subsribers.end(),
			[&](auto eventSubscriberPair) {
				auto [subscriberPtr, pullHandler] = eventSubscriberPair.second;
				return subscriberPtr == &subscriber && eventSubscriberPair.first->GetId() == event->GetId();
			});

		if (search != m_subsribers.end())
		{
			m_subsribers.erase(search);
		}
	}

	void NotifyObservers(IEvent* event) override
	{
		auto iter = m_subsribers.begin();
		while (iter != m_subsribers.end())
		{
			auto& [subscriberEvent, subscriber] = *iter;
			auto& [subscriberPtr, pullHandler] = subscriber;
			++iter;
			if (event->GetId() == subscriberEvent->GetId())
			{
				subscriberPtr->Update(*this, pullHandler);
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::multiset<unsigned int, std::pair<ISubscriber<T>*, std::function<void()>&>> m_subsribers;
};
