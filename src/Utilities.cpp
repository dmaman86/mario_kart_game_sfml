#include "Utilities.h"

const float calcLength(const sf::Vector2f a, const  sf::Vector2f b) {
	return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}
float calcSinDegree(float m_angle) {
    return std::sin(m_angle * 3.141592 / 180);
}

float calcCosDegree(float m_angle) {
    return std::cos(m_angle * 3.141592 / 180);
}



