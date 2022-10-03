#include "AngleTransform.h"

double GetPositiveAngle(double input, double base)
{
	double signResult = std::fmod(input, base);

	return std::fmod(signResult + base, base);
}