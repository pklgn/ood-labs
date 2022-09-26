#pragma once

#include "../pch.h"

template <typename T, typename T2>
class IObservable;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T, typename T2>
class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Update(T const& data, T2 const& metaData) = 0;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T, typename T2>
class IObservable
{
public:
	using ObserverPriority = unsigned short;

	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T, T2>& observer, ObserverPriority priority) = 0;
	virtual void RemoveObserver(IObserver<T, T2>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

// Реализация интерфейса IObservable
template <class T, class T2>
class Observable : public IObservable<T, T2>
{
public:
	using ObserverType = IObserver<T, T2>;
	using ObserverPriorityType = unsigned short;

	void RegisterObserver(ObserverType& observer, ObserverPriorityType priority = 1) override
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

		T2 metaData = GetMetaData();
		
		auto iter = m_observers.begin();
		while (iter != m_observers.end())
		{
			auto [_, observer] = *iter;
			if (observer)
			{
				++iter;
				observer->Update(data, metaData);
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

	virtual T2 GetMetaData() const = 0;

private:
	std::multimap<ObserverPriorityType, ObserverType*> m_observers;
};


// TODO: multimap