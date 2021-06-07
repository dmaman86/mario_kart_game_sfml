#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"

class helpState : public State
{
public:
    helpState(MarioKart::GameDataRef);
    ~helpState() = default;


    void Init()override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override ;
    void Draw() override;
private:
    void setposition() {};
    sf::Sprite m_background;
    sf::Sprite m_back;

    MarioKart::GameDataRef m_data;

    bool m_backMenu;


};

