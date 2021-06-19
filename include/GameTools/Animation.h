#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(sf::Sprite& sprite):m_sprite(sprite){};
    Animation(const std::vector <sf::IntRect >&, sf::Sprite& m_sprite, float, bool is_cyclic,
              unsigned int spinlen );

    void update(float delta, bool is_pressed);
    void spin(float dt);
    void setIndex(int i){m_index = i;}
private:
    void update();
    const std::vector <sf::IntRect> m_data;
    float m_elapsed = {};
    sf::Sprite& m_sprite;
    float m_animationTime;
    int m_index = 0;
    bool m_is_cyclic;
    unsigned int m_vector_len;

};
