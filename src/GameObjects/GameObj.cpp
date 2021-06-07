
#include <iostream>
#include "GameObj.h"
#include "Utilities.h"

GameObj::GameObj(const sf::Texture& tex, const sf::Vector2f loc, const sf::Vector2f pos) : m_location(pos), m_is_in_angle(false) {
	m_sprite.setTexture(tex);
	m_sprite.setPosition(loc);

}

GameObj::GameObj() {

}

void GameObj::setPosition(sf::Vector2f loc) {
	m_sprite.setPosition(loc);
}
#include <iostream>
const bool GameObj::collisionWith(const GameObj& obj) const
{
//std::cout << calcLength(obj.m_sprite.getPosition(), this->m_sprite.getPosition()) << '\n';
	return obj.m_sprite.getGlobalBounds().intersects(this->m_sprite.getGlobalBounds())
		&& (calcLength(obj.m_sprite.getPosition(), this->m_sprite.getPosition()) < 70);
}

sf::Vector2f GameObj::getIntLocation() {
	return m_location;
}

