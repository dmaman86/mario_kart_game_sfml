#include "Banana.h"
#include "Pictures.h"
#include "Sounds.h"

//================================ Constructor ================================
Banana::Banana(const sf::Vector2f& pos) : 
	StaticObject(Pictures::instance().getTexture(Pictures::misc), pos)
{
	m_sprite.setTextureRect(BANANA_RECT);
	m_sprite.setOrigin(float(m_sprite.getTextureRect().width / 2),
					   float(m_sprite.getTextureRect().height / 2));

	m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::banana));
}

