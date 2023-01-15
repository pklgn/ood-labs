#pragma once
#include <SFML/Graphics.hpp>

struct Math
{
	Math() = delete;

	static sf::Vector2f Normalized(const sf::Vector2f& value);
	static float DotProduct(const sf::Vector2f&, const sf::Vector2f&);
};