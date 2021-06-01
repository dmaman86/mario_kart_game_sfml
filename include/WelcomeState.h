#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"

class WelcomeState : public State
{
public:
    WelcomeState(MarioKart::GameDataRef);
    ~WelcomeState() = default;


    virtual void Init()override;
    virtual void HandleEvent(const sf::Event&);
    virtual void Update(float)override;
    virtual void Draw()override;
private:
    void setposition();

    sf::Sprite m_background;
    sf::Sprite m_logoSuper;
    sf::Sprite m_logoMario;
    MarioKart::GameDataRef m_data;
    bool m_nextState;
};
