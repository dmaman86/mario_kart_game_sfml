#include "PlayerBase.h"
#include "Pictures.h"

PlayerBase::PlayerBase(const sf::Texture& tex, const sf::Vector2f loc, const sf::Vector2f pos)
	: GameObj::GameObj(tex, loc, pos), m_start_move(false),
	m_last_location()

{

}
