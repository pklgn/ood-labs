#include "../../../../pch.h"
#include "Math.h"

sf::Vector2f Math::Normalized(const sf::Vector2f& source)
{
	float length = hypotf(source.x, source.y);

	if (length == 0)
	{
		return source;
	}

	return sf::Vector2f(source.x / length, source.y / length);
}

float Math::DotProduct(const sf::Vector2f& first, const sf::Vector2f& second)
{
	return first.x * second.x + first.y * second.y;
}
