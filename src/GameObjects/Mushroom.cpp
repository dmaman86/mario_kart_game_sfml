#include "Mushroom.h"
#include "Pictures.h"
#include "Sounds.h"

//=========================== Constructor ===================================
Mushroom::Mushroom() 
	: StaticObject(Pictures::instance().getTexture(Pictures::misc)) 
{
	m_sprite.setTextureRect(MUSHROOM_RECT);
	m_sprite.setOrigin(float(m_sprite.getTextureRect().width / 2),
					   float(m_sprite.getTextureRect().height / 2));

	m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::boost));
}

