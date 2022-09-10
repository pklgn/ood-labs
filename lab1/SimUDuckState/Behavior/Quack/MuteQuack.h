#include "IQuackBehavior.h"

class MuteQuack : public IQuackBehavior
{
public:
	void Quack() override;
};