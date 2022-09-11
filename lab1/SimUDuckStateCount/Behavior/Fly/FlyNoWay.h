#include "FlyCountable.h"

class FlyNoWay : public FlyCountable
{
public:
	void Fly() override;

protected:
	void CountFlight() override;
};