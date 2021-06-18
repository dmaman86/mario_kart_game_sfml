#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MarioKart.h"
#include "Button.h"

class StateOfMenu : public State
{
public:
    StateOfMenu(MarioKart::GameDataRef);
protected:
    void setVolume(bool);
    void InitOfMenu(MarioKart::GameDataRef);
    sf::Sprite m_background;
    std::shared_ptr<Button> m_back;
    sf::Vector2u m_windowSize;
    sf::Sound m_click;

};

