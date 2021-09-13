#include <iostream>
#include "GameObj.h"
#include "Utilities.h"

//================================= Constructors ==============================
GameObj::GameObj(const sf::Texture& tex, const sf::Vector2f& loc, const sf::Vector2f& pos) :
    m_location(pos),
    m_is_in_angle(false),
    m_is_active (true)
{
	m_sprite.setTexture(tex);
	m_sprite.setPosition(loc);
}

//=============================================================================
GameObj::GameObj():
    m_is_in_angle(false),
    m_is_active(true)
{
}

//=============================================================================
const bool GameObj::collisionWith(const GameObj& obj) const
{
	return obj.m_sprite.getGlobalBounds().intersects(this->m_sprite.getGlobalBounds())
		&& (calcLength( obj.m_sprite.getPosition(), this->m_sprite.getPosition()) 
				< COLLISION_DIS );
}

//=============================================================================
void GameObj::setLocation(const float x, const float y)
{
	m_location.x = x; 
	m_location.y = y;
}

//=============================================================================
void GameObj::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (m_is_active)
		target.draw(m_sprite);
}