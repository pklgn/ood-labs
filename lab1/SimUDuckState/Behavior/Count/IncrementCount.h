#include "ICountBehavior.h"

class IncrementCount : public ICountBehavior
{
public:
	void Increase() override;

	count_type GetCount() override;
private:
	count_type m_count;
};