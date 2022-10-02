#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class Beverage : public IBeverage
{
public:
	Beverage(const std::string & description)
		:m_description(description)
	{
	}

	std::string GetDescription() const override
	{
		return m_description;
	}

private:
	std::string m_description;
};

// Кофе
class Coffee : public Beverage
{
public:
	Coffee(const std::string& description = "Coffee")
		:Beverage(description) 
	{
	}

	double GetCost() const override 
	{
		return 60; 
	}
};

enum class CappuccinoPortionType
{
	COMMON,
	DOUBLE,
};

// Капуччино
class Cappuccino : public Coffee
{
public:
	Cappuccino(CappuccinoPortionType portionType = CappuccinoPortionType::COMMON) 
		: Coffee("Cappuccino" + (portionType == CappuccinoPortionType::DOUBLE) ? " double" : " common")
		, m_portionType(portionType)
	{
	}

	double GetCost() const override 
	{
		return (m_portionType == CappuccinoPortionType::DOUBLE) ? 120 : 80;
	}

private:
	CappuccinoPortionType m_portionType;
};

enum class LattePortionType
{
	COMMON,
	DOUBLE,
};

// Латте
class Latte : public Coffee
{
public:
	Latte(LattePortionType portionType = LattePortionType::COMMON) 
		: Coffee("Latte" + (portionType == LattePortionType::DOUBLE) ? " double" : " common")
		, m_portionType(portionType)
	{
	}

	double GetCost() const override 
	{
		return (m_portionType == LattePortionType::DOUBLE) ? 130 : 90;
	}

private:
	LattePortionType m_portionType;
};

enum class TeaType
{
	GREEN,
	WHITE,
	OOLONG,
	BLACK,
};

// Чай
class Tea : public Beverage
{
public:
	Tea(TeaType type = TeaType::BLACK) 
		: Beverage("Tea") 
		, m_type(type)
	{
	}

	std::string GetTypeDescription() const
	{
		switch (m_type)
		{
		case TeaType::BLACK:
			return "(black)";
		case TeaType::GREEN:
			return "(green)";
		case TeaType::OOLONG:
			return "(oolong)";
		case TeaType::WHITE:
			return "(white)";
		default:
			return "";
		}
	}

	std::string GetDescription() const override
	{
		Beverage::GetDescription() + " " + GetTypeDescription();
	}

	double GetCost() const override 
	{
		return 30; 
	}

private:
	TeaType m_type;
};

enum class MilkShakeSizePrice
{
	SMALL = 50,
	MEDIUM = 60,
	LARGE = 80,
};

// Молочный коктейль
class Milkshake : public Beverage
{
public:
	Milkshake(MilkShakeSizePrice sizePrice = MilkShakeSizePrice::MEDIUM) 
		: Beverage("Milkshake")
		, m_sizePrice(sizePrice)
	{
	}

	std::string GetTypeDescription() const
	{
		switch (m_sizePrice)
		{
		case MilkShakeSizePrice::LARGE:
			return "(large)";
		case MilkShakeSizePrice::MEDIUM:
			return "(medium)";
		case MilkShakeSizePrice::SMALL:
			return "(small)";
		default:
			return "";
		}
	}

	std::string GetDescription() const override
	{
		Beverage::GetDescription() + " " + GetTypeDescription();
	}

	double GetCost() const override 
	{ 
		return static_cast<int>(m_sizePrice); 
	}

private:
	MilkShakeSizePrice m_sizePrice;
};
