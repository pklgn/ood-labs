#include "IQuackBehavior.h"

class MuteQuack : public IQuackBehavior
{
	void Quack() override;
};