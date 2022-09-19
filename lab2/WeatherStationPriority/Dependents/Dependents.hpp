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
	virtual void RegisterObserver(IObserver<T>& observer, unsigned int priority) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual bool CheckRegistration(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer, unsigned int priority) override
	{
		RemoveObserver(observer);
		m_observers[priority].insert(&observer);
	}

	void RemoveObserver(ObserverType& observer) override
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

	bool CheckRegistration(ObserverType& observer)
	{
		for (auto& [priority, observers] : m_observers)
		{
			auto search = observers.find(&observer);
			if (search != observers.end())
			{
				return true;
			}
		}
		
		return false;
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	using ObserversSet = std::set<ObserverType*>;
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
