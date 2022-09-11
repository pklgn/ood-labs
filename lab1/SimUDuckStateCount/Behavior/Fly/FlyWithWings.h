#include "FlyCountable.h"

class FlyWithWings : public FlyCountable
{
public:
	void Fly() override;

protected:
	void CountFlight() override;
};
