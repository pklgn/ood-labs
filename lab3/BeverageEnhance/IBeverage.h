#pragma once

#include <string>
#include <memory>


// Интерфейс "напиток"
class IBeverage
{
public:
	virtual ~IBeverage() = default;

	virtual std::string GetDescription() const = 0;
	virtual double GetCost() const = 0;
};

typedef std::unique_ptr<IBeverage> IBeveragePtr;
