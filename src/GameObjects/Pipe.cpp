#include "Pictures.h"
#include "Pipe.h"
#include "Sounds.h"
Pipe::Pipe(const sf::Vector2f& loc,const sf::Vector2f& pos): StaticObject(Pictures::instance().getTexture(Pictures::misc),loc,pos){

     m_sprite.setTextureRect(sf::Rect(0,53,27,33));
    m_sprite.setOrigin(m_sprite.getTextureRect().width/2,m_sprite.getTextureRect().height/2);
    //m_sound = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::pipe));

}
