#pragma once

#include "../WeatherData.h"

class Display : public IObserver<WeatherEvent>
{
public:
	Display(std::ostream&);

protected:
	std::ostream& m_output;
};
