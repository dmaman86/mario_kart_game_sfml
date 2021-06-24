#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "StateOfMenu.h"
#include "MarioKart.h"

class helpState : public StateOfMenu
{
public:
    // constructor & destructor
    helpState(MarioKart::GameDataRef&);
    ~helpState() = default;

    // virtual functions
    void Init()override;
    void HandleEvent(const sf::Event&) override;
    void Update(const float) override ;
    void Draw() override;
private:
    // privates members
    MarioKart::GameDataRef m_data;
    sf::Sprite m_keyboard;
};

