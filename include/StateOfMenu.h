#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MarioKart.h"

class StateOfMenu : public State
{
public:
  
protected:
    void setVolume(bool);
    void InitOfMenu(MarioKart::GameDataRef);
    sf::Sprite m_background;
    sf::Sprite m_back;
    bool m_backMenu = false;
    sf::Vector2u m_windowSize;
    sf::Sound m_click;

};

