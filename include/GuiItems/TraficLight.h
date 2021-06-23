#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Animation.h"
class TraficLight {

public:
    TraficLight();
    void draw(sf::RenderWindow&);
    void UpdateAnimation(const float time);
    void playSound() { m_sound.play(); };

private:
    sf::Sprite m_sprite;
    Animation m_animation;
    sf::Sound m_sound;
};

