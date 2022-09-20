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
	virtual void Update(T const& data, IObservable<T>& observable) = 0;

	virtual void RegisterObservable(IObservable<T>& observable) = 0;
	virtual void RemoveObservable(IObservable<T>& observable) = 0;
};

template <class T>
class Observer : public IObserver<T>
{
public:
	using ObservableType = IObservable<T>;

	~Observer()
	{
		typename std::set<ObservableType*>::iterator iter = m_observables.begin();
		while (iter != m_observables.end())
		{
			auto* observable = *iter;
			++iter;
			observable->RemoveObserver(*this);
		}
	}

private:
	void RegisterObservable(ObservableType& observable) override
	{
		m_observables.insert(&observable);
	}

	void RemoveObservable(ObservableType& observable) override
	{
		m_observables.erase(&observable);
	}

	std::set<ObservableType*> m_observables;
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

	~Observable()
	{
		typename std::set<ObserverType*>::iterator iter = m_observers.begin();
		while (iter != m_observers.end())
		{
			auto* observer = *iter;
			++iter;
			RemoveObserver(*observer);
		}
	}

	void RegisterObserver(ObserverType& observer) override
	{
		m_observers.insert(&observer);
		observer.RegisterObservable(*this);
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(&observer);
		observer.RemoveObservable(*this);
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
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType*> m_observers;
};
