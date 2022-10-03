#include <iostream>
#include <vector>

#include "../BeverageEnhance/Beverages.h"
#include "../BeverageEnhance/Condiments.h"

int main()
{
	// task1.1
	auto latte = std::make_unique<Latte>(LattePortionType::COMMON);
	std::cout << latte->GetDescription() << " costs " << latte->GetCost() << std::endl;

	auto doubleLatte = std::make_unique<Latte>(LattePortionType::DOUBLE);
	std::cout << doubleLatte->GetDescription() << " costs " << doubleLatte->GetCost() << std::endl;

	// task1.2
	auto cappuccino = std::make_unique<Cappuccino>(CappuccinoPortionType::COMMON);
	std::cout << cappuccino->GetDescription() << " costs " << cappuccino->GetCost() << std::endl;

	auto doubleCappuccino = std::make_unique<Cappuccino>(CappuccinoPortionType::DOUBLE);
	std::cout << doubleCappuccino->GetDescription() << " costs " << doubleCappuccino->GetCost() << std::endl;

	// task1.3
	auto blackTea = std::make_unique<Tea>(TeaType::BLACK);
	std::cout << blackTea->GetDescription() << " costs " << blackTea->GetCost() << std::endl;

	auto whiteTea = std::make_unique<Tea>(TeaType::WHITE);
	std::cout << whiteTea->GetDescription() << " costs " << whiteTea->GetCost() << std::endl;

	// task1.4
	std::vector<MilkShakeSizePrice> sizePrices{ MilkShakeSizePrice::SMALL, MilkShakeSizePrice::MEDIUM, MilkShakeSizePrice::LARGE };
	for (auto& sizePrice : sizePrices)
	{
		auto milkShake = std::make_unique<Milkshake>(sizePrice);
		std::cout << milkShake->GetDescription() << " costs " << milkShake->GetCost() << std::endl;
	}

	// task2.1
	auto coffee = std::make_unique<Coffee>();
	auto cinnamonCoffee = std::make_unique<Cinnamon>(std::move(coffee));
	auto creamCinnamonCoffee = std::make_unique<Cream>(std::move(cinnamonCoffee));

	std::cout << creamCinnamonCoffee->GetDescription() << " costs " << creamCinnamonCoffee->GetCost() << std::endl;

	// task2.2
	auto anotherLatte = std::make_unique<Latte>();
	auto cinnamonLatte = std::make_unique<Cinnamon>(std::move(anotherLatte));
	auto chocolateCinnamonCoffee = std::make_unique<Chocolate>(std::move(cinnamonLatte), 3);

	std::cout << chocolateCinnamonCoffee->GetDescription() << " costs " << chocolateCinnamonCoffee->GetCost() << std::endl;

	// task2.3
	auto tea = std::make_unique<Tea>();
	auto liquorTea = std::make_unique<Liquor>(std::move(tea), LiquorType::NUT);
	auto chocolateLiquorTea = std::make_unique<Chocolate>(std::move(liquorTea), 6);

	std::cout << chocolateLiquorTea->GetDescription() << " costs " << chocolateLiquorTea->GetCost() << std::endl;
}