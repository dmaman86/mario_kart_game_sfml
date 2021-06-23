#include "Pictures.h"
#include "Pipe.h"

//================================ Constructor ================================
Pipe::Pipe(const sf::Vector2f& pos): 
	StaticObject(Pictures::instance().getTexture(Pictures::misc),pos){

	m_sprite.setTextureRect(PIPE_RECT);
    m_sprite.setOrigin(float(m_sprite.getTextureRect().width/2),
					   float(m_sprite.getTextureRect().height/2));
}
