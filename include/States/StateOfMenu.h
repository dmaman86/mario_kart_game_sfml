#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MarioKart.h"
#include "Button.h"

class StateOfMenu : public State
{
public:
    //constructor
    StateOfMenu(MarioKart::GameDataRef);

protected:
    //protected functions
    void setVolume(bool);
    void InitOfMenu(MarioKart::GameDataRef);
    
    //protected members
    sf::Sprite m_background;
    sf::Sprite m_logo;
    std::shared_ptr<Button> m_back;
    sf::Vector2u m_windowSize;
    sf::Sound m_click;
    bool m_soundOn;
};

