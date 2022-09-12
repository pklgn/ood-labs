#include "IFlyBehavior.h"

class FlyNoWay : public IFlyBehavior
{
public:
	bool Fly() override;
};