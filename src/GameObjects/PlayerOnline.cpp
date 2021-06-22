#include "PlayerOnline.h"
#include "Pictures.h"

PlayerOnline::PlayerOnline(const std::string& sprite,
                           const sf::Vector2f& loc,
                           const sf::Vector2f& pos)
	: PlayerBase::PlayerBase(Pictures::instance().getTexture(sprite), loc, pos)

{
	m_sprite.setTextureRect(sf::Rect(0, 0, 33, 33));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.scale(3, 3);
}
