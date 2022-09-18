#pragma once

#include "../pch.h"

template <class T>
class Observable;

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
	virtual void Update(T const& data, Observable<T>& observable) = 0;
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
	virtual void RegisterObserver(IObserver<T>& observer, unsigned int priority) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

// Реализация интерфейса IObservable
template <class T>
class Observable : public IObservable<T>
{
public:
	using Observer = IObserver<T>;

	void RegisterObserver(Observer& observer, unsigned int priority) override
	{
		RemoveObserver(observer);
		m_observers[priority].insert(&observer);
	}

	void RemoveObserver(Observer& observer) override
	{
		for (auto& [priority, observers] : m_observers)
		{
			auto search = observers.find(&observer);
			if (search != observers.end())
			{
				observers.erase(search);
				break;
			}
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		
		for (auto& observers: m_observers)
		{
			NotifyObserversSet(data, observers.second);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	using ObserversSet = std::set<Observer*>;
	std::map<unsigned int, ObserversSet> m_observers;

	void NotifyObserversSet(T& data, ObserversSet& observersSet)
	{
		typename ObserversSet::iterator iter = observersSet.begin();
		while (iter != observersSet.end())
		{
			auto* observer = *iter;
			if (observer)
			{
				++iter;
				observer->Update(data, *this);
			}
			else
			{
				iter = observersSet.erase(iter);
			}
		}
	}
};
