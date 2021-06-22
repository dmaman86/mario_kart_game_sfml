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


    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;

private:
    void setColorShape(sf::CircleShape&);
    sf::Text createFont(std::string, sf::Color, int);
    MarioKart::GameDataRef m_data;
    sf::Sprite m_title;
    sf::Sprite m_rectangle;
    sf::CircleShape m_shapeSound;
    sf::CircleShape m_shapeMusic;
    sf::Text m_messageMusic;
    sf::Text m_messageSound;
    bool onSound = true;
};

