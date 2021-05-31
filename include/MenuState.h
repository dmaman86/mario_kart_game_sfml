#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"

class MenuState : public State
{
public:
    MenuState(MarioKart::GameDataRef);
    ~MenuState() = default;


    virtual void Init()override;
    virtual void HandleEvent(const sf::Event&);
    virtual void Update(float) {};
    virtual void Draw()override;

private:
    sf::Sprite m_background;
    sf::Sprite m_logo;
    MarioKart::GameDataRef m_data;

};
