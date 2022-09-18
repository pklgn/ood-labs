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
	virtual void Update(T const& data) = 0;

	virtual void RegisterObservable(Observable<T>& observable) = 0;
	virtual void RemoveObservable(Observable<T>& observable) = 0;
};

template <class T>
class Observer : public IObserver<T>
{
public:
	using ObservableType = Observable<T>;

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

	void RegisterObservable(ObservableType& observable) override
	{
		if (observable.CheckRegistration(*this))
		{
			m_observables.insert(&observable);
		}
	}

	void RemoveObservable(ObservableType& observable) override
	{
		auto search = m_observables.find(&observable);
		if (!observable.CheckRegistration(*this) && search != m_observables.end())
		{
			m_observables.erase(search);
		}
	}

private:
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
	virtual void RegisterObserver(Observer<T>& observer) = 0;
	virtual void RemoveObserver(Observer<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

// Реализация интерфейса IObservable
template <class T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = Observer<T>;

	~Observable()
	{
		//std::for_each(m_observers.begin(), m_observers.end(), [&](auto& observer) { RemoveObserver(*observer); });
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
		for (auto& observer : m_observers)
		{
			observer->Update(data);
		}
	}

	bool CheckRegistration(ObserverType& observer)
	{
		return m_observers.find(&observer) != m_observers.end();
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::set<ObserverType*> m_observers;
};
