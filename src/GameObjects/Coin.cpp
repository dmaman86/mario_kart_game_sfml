#include "Coin.h"
#include "Pictures.h"
#include "Sounds.h"

// static definition
int Coin::m_num_coins = 0;
int Coin::m_num_collected = 0;
// const animation
const auto ANIMATION_TIME = 0.2f;

//========================== Constructor / Destructor =========================
Coin::Coin(const sf::Vector2f& pos) :
	StaticObject(Pictures::instance().getTexture(Pictures::misc), pos)
	,m_animation(Pictures::instance().getCoinAnim(),
                 m_sprite,
                 ANIMATION_TIME,
                 true,
                 (unsigned int)(Pictures::instance().getCoinAnim().size()))
{
	m_sprite.setTextureRect(COIN_RECT);
	m_sprite.setOrigin(float(m_sprite.getTextureRect().width / 2),
		float(m_sprite.getTextureRect().height / 2));

	m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::coin));

	++m_num_coins;
}
//=============================================================================
Coin::~Coin()
{
	--m_num_coins;
	m_num_collected = 0;
}