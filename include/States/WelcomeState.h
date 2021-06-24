#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"

class WelcomeState : public State
{
public:
    // constructor & destructor
    WelcomeState(MarioKart::GameDataRef);
    ~WelcomeState() = default;

    // virtual functions
    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(const float) override;
    void Draw() override;
private:
    // privates members
    MarioKart::GameDataRef m_data;

    sf::Sprite m_background;
    sf::Sprite m_logoMario;
    sf::Text m_text;

    bool m_nextState;
    bool m_showText;
    float mTextEffectTime;
};
