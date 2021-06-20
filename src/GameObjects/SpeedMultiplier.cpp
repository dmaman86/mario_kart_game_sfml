#include "SpeedMultiplier.h"
#include "Pictures.h"
SpeedMultiplier::SpeedMultiplier(sf::Vector2f loc, const sf::Vector2f pos) : StaticObject(Pictures::instance().getTexture(Pictures::misc), loc, pos) {

	m_sprite.setTextureRect(sf::Rect(130, 154, 19, 19));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
}

