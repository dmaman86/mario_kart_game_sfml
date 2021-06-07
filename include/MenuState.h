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
    using Extra = std::pair< sf::Sprite, bool >;
    void setVolume();
    void setposition();
    void updateColors(size_t);
    std::vector< Pair > m_buttons;
    sf::Sprite m_background;
    Extra m_carrer;
    Extra m_online;

    MarioKart::GameDataRef m_data;
    sf::Sound m_click;
    bool m_showExtra;
};
