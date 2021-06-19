#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
class TraficLight {

public:
    TraficLight();
    void draw(sf::RenderWindow&);
    void updateAnimation(float time);


private:
    sf::Sprite m_sprite;
    Animation m_animation;
};

