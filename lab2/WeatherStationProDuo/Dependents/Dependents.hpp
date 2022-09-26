#pragma once

#include "../pch.h"

template <typename T>
class IObservable;

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
	virtual void Update(T const& data) = 0;
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
	virtual void RegisterObserver(IObserver<T>& observer, unsigned short priority) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

// Реализация интерфейса IObservable
template <class T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer, unsigned short priority = 1) override
	{
		RemoveObserver(observer);
		m_observers.emplace(priority, &observer);
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto search = std::find_if(m_observers.begin(), m_observers.end(),
			[&](auto priorityObserverPair) { return priorityObserverPair.second == &observer; });

		if (search != m_observers.end())
		{
			m_observers.erase(search);
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		
		auto iter = m_observers.begin();
		while (iter != m_observers.end())
		{
			auto [_, observer] = *iter;
			if (observer)
			{
				++iter;
				observer->Update(data);
			}
			else
			{
				iter = m_observers.erase(iter);
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::multimap<unsigned short, ObserverType*> m_observers;
};
