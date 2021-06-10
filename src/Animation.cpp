#include <iostream>
#include "Animation.h"
#include "Pictures.h"

const auto AnimationTime = sf::seconds(3.f);

Animation::Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite)
    : m_dir(dir), m_sprite(sprite),m_data(data),m_index(0)
{
    m_sprite.setTexture(Pictures::instance().getTexture(Pictures::drivers));
    update();
}

void Animation::direction(Direction dir)
{

    if (m_dir == dir || dir == Direction::Stay)
    {
        return;
    }

    m_dir = dir;
    update();
}

void Animation::update(sf::Time i, bool is_pressed) {

    if (!is_pressed)
    {
        m_index -- ;
        if(m_index < 0) m_index = 0;
    }

    else {
        m_elapsed += i;
        if(i.asMilliseconds() <= 100.f)++m_index;
        else
        if (m_elapsed >= AnimationTime) {
            m_elapsed -= AnimationTime;
            if (m_index < m_data.m_data.size() - 1)
                ++m_index;

        }
        m_index %= m_data.m_data.size();
    }
    update();
}

void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data[m_index]);
   // std::cout << m_data.m_data[m_index].left <<"  "<<m_data.m_data[m_index].top<<" \n" ;
}
