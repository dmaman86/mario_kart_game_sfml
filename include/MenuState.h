#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "State.h"
#include "MarioKart.h"
#include "Sounds.h"

class MenuState : public State
{
public:
    MenuState(MarioKart::GameDataRef&);
    ~MenuState() = default;

    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
    void Resume() override;
private:
    using Pair = std::pair< sf::Sprite, bool >;
    void setVolume();
    void updateColors(size_t);
    std::vector< Pair > m_buttons;
    sf::Sprite m_background;
    sf::Sprite m_letsPlay;
    sf::Sprite m_help;
    sf::Sprite m_about;
    sf::Sprite m_settings;

    MarioKart::GameDataRef m_data;
    sf::Sound m_click;

    bool m_helpState;
    bool m_aboutState;
    bool m_settingsState;
};
