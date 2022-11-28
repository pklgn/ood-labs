#pragma once
#include "ILineStyleEnumerator.h"
#include "../../../Shape/IShape.h"

template <class T>
class LineStyleEnumerator : public ILineStyleEnumerator
{
public:
	LineStyleEnumerator(const T& items)
		: m_items(items)
	{
	}

	void EnumerateAll(std::function<void(std::shared_ptr<ILineStyle>)> callback) override
	{
		for (auto& item : m_items)
		{
			callback(item->GetLineStyle());
		}
	}

private:
	const T& m_items;
};