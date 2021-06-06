
#include "Utilities.h"

const float calcLength(const sf::Vector2f a, const  sf::Vector2f b) {
	return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}

