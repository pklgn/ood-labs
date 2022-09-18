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
	virtual void RegisterObserver(IObserver<T>& observer) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

// Реализация интерфейса IObservable
template <class T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer) override
	{
		m_observers.insert(&observer);
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto search = m_observers.find(&observer);
		if (search != m_observers.end())
		{
			m_observers.erase(search);
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		typename std::set<ObserverType*>::iterator iter = m_observers.begin();
		while (iter != m_observers.end())
		{
			auto* observer = *iter;
			if (observer)
			{
				++iter;
				observer->Update(data, *this);
			}
			else
			{
				iter = m_observers.erase(iter);
			}
		}
		//std::for_each(m_observers.begin(), m_observers.end(), [&](auto& observer) { observer->Update(data, *this); });
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType*> m_observers;
};
