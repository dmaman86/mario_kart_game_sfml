
#include <iostream>
#include "GameObj.h"
#include "Utilities.h"

GameObj::GameObj(const sf::Texture& tex, const sf::Vector2f loc, const sf::Vector2f pos) :
    m_location(new sf::Vector2f(pos)),
    m_is_in_angle(false)
    //m_is_active (true)
{
	m_sprite.setTexture(tex);
	m_sprite.setPosition(loc);

}

GameObj::GameObj() {

}

void GameObj::setPosition(sf::Vector2f loc) {
	m_sprite.setPosition(loc);
}
const bool GameObj::collisionWith(const GameObj& obj) const
{
	return obj.m_sprite.getGlobalBounds().intersects(this->m_sprite.getGlobalBounds())
		&& (calcLength(obj.m_sprite.getPosition(), this->m_sprite.getPosition()) < 70);
}

void GameObj::playSound()
{
	this->m_sound.play();
}

sf::Vector2f GameObj::getIntLocation() {
	return *m_location;
}

