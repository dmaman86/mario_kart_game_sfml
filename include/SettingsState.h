#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MarioKart.h"
#include "StateOfMenu.h"

class SettingsState : public StateOfMenu
{
public:
    SettingsState(MarioKart::GameDataRef&);
    ~SettingsState() = default;


    virtual void Init()override;
    virtual void HandleEvent(const sf::Event&);
    virtual void Update(float)override;
    virtual void Draw()override;

private:
    MarioKart::GameDataRef m_data;
    sf::Sprite m_title;
    sf::CircleShape m_shapeSound;
    sf::CircleShape m_shapeMusic;
    sf::Text m_messageMusic;
    sf::Text m_messageSound;
    sf::Sound m_click;

    bool onSound = true;
};

