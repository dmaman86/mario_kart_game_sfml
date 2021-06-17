#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
class StartCloud {


public:
    StartCloud();
    void draw(sf::RenderWindow&);
    void updateAnimation(sf::Time);

private:
    sf::Sprite m_sprite;
    Animation m_animation;
};


