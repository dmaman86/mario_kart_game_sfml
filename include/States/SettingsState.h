#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MarioKart.h"
#include "StateOfMenu.h"

class SettingsState : public StateOfMenu
{
public:
    // constructor & destructor
    SettingsState(MarioKart::GameDataRef&);
    ~SettingsState() = default;

    // virtual functions
    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(const float) override;
    void Draw() override;

private:
    // privates functions
    void setColorShape(sf::CircleShape&);

    // privates members
    sf::Text createFont(const std::string&, const sf::Color&, const int);
    MarioKart::GameDataRef m_data;
    sf::Sprite m_title;
    sf::RectangleShape m_rectangle;
    // sf::Sprite m_rectangle;
    sf::CircleShape m_shapeSound;
    sf::CircleShape m_shapeMusic;
    sf::Text m_messageMusic;
    sf::Text m_messageSound;
    bool onSound;

};

