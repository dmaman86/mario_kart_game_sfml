#include "Pictures.h"
#include "Pipe.h"

Pipe::Pipe(sf::Vector2f loc,const sf::Vector2f pos): StaticObject(Pictures::instance().getTexture(Pictures::misc),loc,pos), m_renderCount(0){

     m_sprite.setTextureRect(sf::Rect(0,53,29,33));
    m_sprite.setOrigin(m_sprite.getTextureRect().width/2,m_sprite.getTextureRect().height/2);
}

void Pipe::draw(sf::RenderWindow& win)
{
	//if (++m_renderCount > 15)
	//{
	//	m_renderCount = 0;
	//	m_is_in_angle = false;
	//}
	//else
		StaticObject::draw(win);
}
