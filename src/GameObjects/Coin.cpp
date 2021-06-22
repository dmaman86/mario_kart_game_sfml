#include "Coin.h"
#include "Pictures.h"
#include "Sounds.h"
// static definition
int Coin::m_num_coins = 0;
int Coin::m_num_collected = 0;
const auto AnimationTime = 0.2f;
Coin::Coin(const sf::Vector2f& loc, const sf::Vector2f& pos) :
	StaticObject(Pictures::instance().getTexture(Pictures::misc), loc, pos) ,
    m_animation(Pictures::instance().getCoinAnim(),m_sprite,AnimationTime,true,Pictures::instance().getCoinAnim().size())
{
	m_sprite.setTextureRect(sf::Rect(5, 160, 15, 25));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2,
		m_sprite.getTextureRect().height / 2);

	m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::coin));

	++m_num_coins;
}

Coin::~Coin()
{
	--m_num_coins;
	m_num_collected = 0;
}

// get functions :
//===================================================
const int Coin::getCount()
{
	return m_num_coins;
}

//===================================================
const int Coin::getCollected()
{
	return m_num_collected;
}
//===================================================

void Coin::updateAnimation(float time) {
    m_animation.update(time, true);

}
