#include <iostream>
#include "Animation.h"
#include "Pictures.h"
#include "Macros.h"

//============================= Constructor ======================================
Animation::Animation(const std::vector <sf::IntRect >& data, sf::Sprite& m_sprite,
	const float animationtime, const  bool is_cyclic,
                     unsigned int len): m_is_cyclic(is_cyclic), m_vector_len(len),
                                        m_sprite(m_sprite),
                                        m_data(data),
                                        m_index(0),
                                        m_animationTime(animationtime),
                                        m_elapsed()
{
    update();
}

//================================ Public functions ===========================
void Animation::update(float delta, bool is_pressed) {
    //add the the count time
    m_elapsed +=delta;
    //check if it is time to change animation
    if(m_elapsed > m_animationTime){
       m_elapsed -= m_animationTime;
       //if the forward key is not press take one animation back
        if (!is_pressed){
            m_index -- ;
        if(m_index < 0) m_index = 0;
    }
    else
         if ( m_index < int(m_vector_len) - 1) {
                ++m_index;
         }
         //if the animation is not cyclit the animation stay on the last one
         else if(m_is_cyclic)m_index++;
        }
    m_index %= m_vector_len;

    update();
}

//=============================================================================
void Animation::spin()
{
    if(m_index == m_data.size()-1)
        m_sprite.setScale(-PlayerDefinitions::SCALE_PLAYER, PlayerDefinitions::SCALE_PLAYER);
    else if  (m_index == 0)
        m_sprite.setScale(PlayerDefinitions::SCALE_PLAYER, PlayerDefinitions::SCALE_PLAYER);
    //check in witch side the sprite is and spin the the other side
    (m_sprite.getScale().x > 0 )? m_index+=2:m_index--;

    m_index %= m_data.size();

    update();
}

//=============================== private functions ===========================
void Animation::update()
{
	m_sprite.setTextureRect(m_data[m_index]);
}