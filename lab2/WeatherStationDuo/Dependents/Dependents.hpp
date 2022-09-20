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
};

template <typename T>
using ObserverPtrType = std::shared_ptr<IObserver<T>>;

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(const ObserverPtrType<T>& observer, unsigned int priority) = 0;
	virtual void RemoveObserver(const ObserverPtrType<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

template <typename Map, typename F>
static const void MapEraseIf(Map& m, F&& pred)
{
	for (typename Map::iterator i = m.begin(), end = m.end(); (i = std::find_if(i, end, std::forward<F>(pred))) != end; m.erase(i++));
}

// Реализация интерфейса IObservable
template <class T, class Comp = std::less<unsigned int>>
class Observable : public IObservable<T>
{
public:
	void RegisterObserver(const ObserverPtrType<T>& observer, unsigned int priority) final
	{
		RemoveObserver(observer);
		m_observers.emplace(priority, ObserverWeakPtrType(observer));
	}

	void RemoveObserver(const ObserverPtrType<T>& observer) final
	{
		MapEraseIf(m_observers, [&](auto& el) { return el.second.lock() == observer; });
	}

	void NotifyObservers() final
	{
		T data = GetChangedData();
		
		for (auto it = m_observers.begin(), end = m_observers.end(); it != end;)
		{
			auto slowIt = it;
			auto& [_, observer] = *it;
			++it;
			if (auto ptr = observer.lock(); ptr != nullptr)
			{
				ptr->Update(data, *this);
			}
			else
			{
				m_observers.erase(slowIt);
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	using ObserverWeakPtrType = std::weak_ptr<IObserver<T>>;

	std::multimap<unsigned int, ObserverWeakPtrType, Comp> m_observers;
};


// TODO: multimap