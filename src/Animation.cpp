#include <iostream>
#include "../../../CLionProjects/mario_kart_game_sfml/include/Animation.h"

#include "Pictures.h"

const auto AnimationTime = sf::seconds(0.3f);

Animation::Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite)
    : m_data(data), m_dir(dir), m_sprite(sprite)
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

void Animation::update(float i)
{
    m_index ++;
    m_index %= m_data.m_data.size();

//    m_elapsed += delta;
//    if (m_elapsed >= AnimationTime)
//    {
//        m_elapsed -= AnimationTime;
//        ++m_index;
//        m_index %= m_data.m_data.size();
        update();
//    }
}

void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data[m_index]);
    std::cout << m_data.m_data[m_index].left <<"  "<<m_data.m_data[m_index].top<<" \n" ;
}
