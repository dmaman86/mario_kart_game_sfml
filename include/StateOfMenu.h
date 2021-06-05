#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"

class StateOfMenu : public State
{
public:
  
protected:
    void InitOfMenu(MarioKart::GameDataRef);
    sf::Sprite m_background;
    sf::Sprite m_back;
    bool m_backMenu = false;
    sf::Vector2u m_windowSize;
};

