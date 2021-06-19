#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(sf::Sprite& sprite):m_sprite(sprite){};
    Animation(const std::vector <sf::IntRect >&, sf::Sprite& m_sprite,float );

    void update(sf::Time i, bool is_pressed);
    void spin(float dt);
    void setIndex(int i){m_index = i;}
private:
    void update();

    const std::vector <sf::IntRect> m_data;
    sf::Time m_elapsed = {};

    int m_index = 0;
    sf::Sprite& m_sprite;
    float m_animationTime;

};
