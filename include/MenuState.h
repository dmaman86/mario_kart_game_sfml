#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "State.h"
#include "MarioKart.h"
#include "Sounds.h"
#include "Button.h"

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
    void stopMusic();
private:
    enum class Options
    {
        About,
        Help,
        Settings,
        LetPlay,
        Online,
        Carer
    };
    std::map<Options, std::shared_ptr<Button>> m_buttons;
    sf::Sprite m_background;

    MarioKart::GameDataRef m_data;
    sf::Sound m_click;
    sf::Music m_startMusic;
    bool m_showExtra;

    void setVolume();
    void updateColors(const sf::Vector2f&);
};
