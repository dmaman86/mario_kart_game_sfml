#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "StateOfMenu.h"
#include "MarioKart.h"

class helpState : public StateOfMenu
{
public:
    helpState(MarioKart::GameDataRef&);
    ~helpState() = default;


    void Init()override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override ;
    void Draw() override;
private:
    MarioKart::GameDataRef m_data;
    sf::Sprite m_keyboard;

};

