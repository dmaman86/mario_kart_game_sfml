#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "State.h"
#include "MarioKart.h"
#include "Sounds.h"
#include "Button.h"
#include "Macros.h"

class MenuState : public State
{
public:
    // constructor & destructor
    MenuState(MarioKart::GameDataRef&);
    ~MenuState() = default;
    // virtual functions
    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
    // return to this state
    void Resume() override;
    // local function
    void stopMusic();
private:
    // private members
    enum class Options
    {
        About,
        Help,
        Settings,
        LetPlay
    };
    std::map<Options, std::shared_ptr<Button>> m_buttons;
    std::shared_ptr<Button> m_button_online;
    std::shared_ptr<Button> m_button_carer;
    sf::Sprite m_background;
    sf::RectangleShape m_rect_logo;

    MarioKart::GameDataRef m_data;
    sf::Sound m_click;
    bool m_showExtra;
    bool m_onSound;
    // private functions
    void setVolume();
    void updateColors(const sf::Vector2f&);
};
