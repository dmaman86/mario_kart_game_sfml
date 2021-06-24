#include "Utilities.h"

const auto PIE = 3.141592f;
const auto DEG_180 = 180.f;

const float calcLength(const sf::Vector2f a, const  sf::Vector2f b) {
	return std::sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

const float calcSinDegree(const float angle) {
    return std::sin(angle * PIE / DEG_180);
}

const float calcCosDegree(const float angle) {
    return std::cos(angle * PIE / DEG_180);
}



