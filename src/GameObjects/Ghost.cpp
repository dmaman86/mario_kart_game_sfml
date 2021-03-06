#include "Ghost.h"
#include "Pictures.h"
#include "Sounds.h"

//================================ Constructor ================================
Ghost::Ghost() : 
	StaticObject(Pictures::instance().getTexture(Pictures::misc)) 
{
	m_sprite.setTextureRect(sf::Rect(182, 70, 20, 15));
	m_sprite.setOrigin(float(m_sprite.getTextureRect().width / 2),
					   float(m_sprite.getTextureRect().height / 2));
	
	m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::ghost));
}

