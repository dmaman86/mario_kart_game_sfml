#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "MarioKart.h"

class MenuState : public State
{
public:
    MenuState(MarioKart::GameDataRef);
    ~MenuState() = default;


    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
private:
    void setposition();
    std::vector<sf::Sprite>m_spriteVector;
    sf::Sprite m_background;
    sf::Sprite m_letsPlay;
    sf::Sprite m_help;
    sf::Sprite m_about;
    sf::Sprite m_online;
    sf::Sprite m_settings;
    sf::Sprite m_career;

    MarioKart::GameDataRef m_data;

    bool m_helpState;
    bool m_aboutState;
    bool m_settingsState;

};
