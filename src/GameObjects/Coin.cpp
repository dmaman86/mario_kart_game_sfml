#include "Coin.h"
#include "Pictures.h"

// static definition
int Coin::m_num_coins = 0;
int Coin::m_num_collected = 0;

Coin::Coin(sf::Vector2f loc, const sf::Vector2f pos) : 
	StaticObject(Pictures::instance().getTexture(Pictures::misc), loc, pos) 
{
	m_sprite.setTextureRect(sf::Rect(5, 160, 15, 25));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2,
		m_sprite.getTextureRect().height / 2);

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