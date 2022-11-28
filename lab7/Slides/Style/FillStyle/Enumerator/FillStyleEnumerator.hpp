#pragma once
#include "IFillStyleEnumerator.h"
#include "../../../Shape/IShape.h"

template<class T>
class FillStyleEnumerator : public IFillStyleEnumerator
{
public:
	FillStyleEnumerator(T& items)
		: m_items(items)
	{
	}

	void EnumerateAll(std::function<void(std::shared_ptr<IFillStyle>)> callback) override
	{
		for (auto& item : m_items)
		{
			callback(item->GetFillStyle());
		}
	}

private:
	T& m_items;
};