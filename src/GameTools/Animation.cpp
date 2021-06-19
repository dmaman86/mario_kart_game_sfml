#include <iostream>
#include "Animation.h"
#include "Pictures.h"
#include "Macros.h"

Animation::Animation(const std::vector <sf::IntRect >& data, sf::Sprite& m_sprite, float animationtime, bool is_cyclic,
                     unsigned int len): m_is_cyclic(is_cyclic), m_vector_len(len),
                                        m_sprite(m_sprite),
                                        m_data(data),
                                        m_index(0),
                                        m_animationTime(animationtime),
                                        m_elapsed()
{
    // TODO: לירן למה זה? אם אתה שם בהערה את השורה זה מסתדר באונליין
    update();
}



void Animation::update(float delta, bool is_pressed) {

    m_elapsed +=delta;
    if(m_elapsed > m_animationTime){
       m_elapsed -= m_animationTime;
        if (!is_pressed){
            m_index -- ;
        if(m_index < 0) m_index = 0;
    }
    else

         if ( m_index < m_vector_len - 1) {
                ++m_index;
         }
         else if(m_is_cyclic)m_index++;
        }
    m_index %= m_vector_len;



    update();
}

void Animation::update()
{
    m_sprite.setTextureRect(m_data[m_index]);
}

void Animation::spin(float dt) {


    if(m_index == m_data.size()-1)
        m_sprite.setScale(-SCALEPLAYER,SCALEPLAYER);
    else if  (m_index == 0)
        m_sprite.setScale(SCALEPLAYER,SCALEPLAYER);

    (m_sprite.getScale().x > 0 )? m_index+=2:m_index--;

    m_index %= m_data.size();


    update();
}
