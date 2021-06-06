#pragma once
#include <SFML/Graphics.hpp>

	float calcLength(sf::Vector2f a, sf::Vector2f b) {
		return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
	}

