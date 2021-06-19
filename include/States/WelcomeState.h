#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"

class WelcomeState : public State
{
public:
    WelcomeState(MarioKart::GameDataRef);
    ~WelcomeState() = default;


    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
private:
    sf::Sprite m_background;
    sf::Sprite m_logoSuper;
    sf::Sprite m_logoMario;
    MarioKart::GameDataRef m_data;
    sf::Text m_text;
    bool m_nextState;
    bool m_showText;
    float mTextEffectTime;
};
