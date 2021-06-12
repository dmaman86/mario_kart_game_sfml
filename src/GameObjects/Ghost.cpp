#include "Ghost.h"
#include "Pictures.h"

Ghost::Ghost(sf::Vector2f loc, const sf::Vector2f pos) : StaticObject(Pictures::instance().getTexture(Pictures::misc), loc, pos) {

	m_sprite.setTextureRect(sf::Rect(182, 70, 20, 15));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
}

