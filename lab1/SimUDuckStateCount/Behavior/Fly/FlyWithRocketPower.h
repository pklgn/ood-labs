#include "FlyCountable.h"

class FlyWithRocketPower : public FlyCountable
{
public:
	void Fly() override;

protected:
	void CountFlight() override;
};