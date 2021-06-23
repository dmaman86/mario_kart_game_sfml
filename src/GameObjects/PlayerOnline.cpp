#include "PlayerOnline.h"
#include "Pictures.h"

//================================= Constructor ==================================
PlayerOnline::PlayerOnline(const std::string& sprite,
                           const sf::Vector2f& loc,
                           const sf::Vector2f& pos)
	: PlayerBase::PlayerBase(Pictures::instance().getTexture(sprite), loc, pos)
{
	m_sprite.setTextureRect(DRIVER_RECT);
	m_sprite.setOrigin(float(m_sprite.getTextureRect().width / 2),
					   float(m_sprite.getTextureRect().height / 2));
	m_sprite.scale(STANDART_SCALE);
}
