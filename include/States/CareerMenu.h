#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "State.h"
#include "MarioKart.h"
#include "StateOfMenu.h"
#include "Button.h"

class CareerMenu: public StateOfMenu
{
public:
    CareerMenu(MarioKart::GameDataRef&);
    ~CareerMenu() = default;

    void Init()override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
    void Resume() override;
private:
    enum class Options
    {
        Carer,
        Time,
        CollectCoins,
        DK,
        Garage,
        Save,
        Back
    };

    sf::Sprite m_driver;
    sf::Sprite m_title;
    sf::Text m_name;
    sf::Text m_moneys;
    sf::Text m_car;
    MarioKart::GameDataRef m_data;
    sf::Sprite m_driverUser;
    std::map<Options, std::shared_ptr<Button>> m_buttons;
    sf::RectangleShape m_rect;


    enum Foo {
        Boewser,
        Dk,
        Mario,
        Koopa,
        Luigi,
        Peach,
        Toad,
        Yoshi
    };

    void saveUser();
    void resetButtons(Options);
    void updateColors(const sf::Vector2f);
};




