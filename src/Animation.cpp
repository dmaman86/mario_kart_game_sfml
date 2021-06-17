#include <iostream>
#include "Animation.h"
#include "Pictures.h"

Animation::Animation(const std::vector <sf::IntRect >& data, sf::Sprite& sprite,float animationtime)
    :m_sprite(sprite),m_data(data),m_index(0),m_animationTime(animationtime),m_elapsed(sf::Time::Zero){
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::drivers));
    update();
}



void Animation::update(sf::Time delta, bool is_pressed) {
    m_elapsed += delta;

    if(m_elapsed >= sf::seconds(1.f)){
        m_elapsed -= sf::seconds(1.f);
        std::cout << m_elapsed.asSeconds()<<"\n";
    if (!is_pressed){
        m_index -- ;
        if(m_index < 0) m_index = 0;
    }
    else
        if (m_index < m_data.size() - 1) {
            ++m_index;
            m_index %= m_data.size();
        }
        update();

        }

}

void Animation::update()
{
    m_sprite.setTextureRect(m_data[m_index]);
}

void Animation::spin(float dt) {


    if(m_index == m_data.size()-1)
        m_sprite.setScale(-3,3);
    else if  (m_index == 0)
        m_sprite.setScale(3,3);

    (m_sprite.getScale().x > 0 )? m_index+=2:m_index--;

    m_index %= m_data.size();


    update();
}
