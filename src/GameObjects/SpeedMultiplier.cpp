#include "SpeedMultiplier.h"
#include "Pictures.h"
#include "Sounds.h"
SpeedMultiplier::SpeedMultiplier(const sf::Vector2f& loc, const sf::Vector2f& pos) : StaticObject(Pictures::instance().getTexture(Pictures::misc), loc, pos) {

	m_sprite.setTextureRect(sf::Rect(131, 147, 20, 20));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);

	m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::boost));

}

