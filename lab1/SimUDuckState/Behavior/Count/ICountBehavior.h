using count_type = size_t;

struct ICountBehavior
{
	virtual void Increase() = 0;
	virtual count_type GetCount() = 0;
	virtual ~ICountBehavior() = default;
};