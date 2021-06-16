#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "MarioKart.h"
#include "UserCareer.h"
#include "StateOfMenu.h"

class CareerMenu: public StateOfMenu
{
public:
    CareerMenu(MarioKart::GameDataRef&, UserCareer &);
    ~CareerMenu() = default;

    void Init()override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
private:
    void saveUser();

    //sf::Sprite m_time;
    //sf::Sprite m_dk;
    //sf::Sprite m_coin;
    //sf::Sprite m_garage;
    sf::Sprite m_driver;
    sf::Text m_name;
    sf::Text m_moneys;
    sf::Text m_car;
    //sf::Sprite m_career;
    //sf::Sprite m_save;
    MarioKart::GameDataRef m_data;

    using Pair = std::pair< sf::Sprite, bool >;
    std::vector< Pair > m_buttons;
    //bool m_backMenu;
   // sf::Sound m_click;
    UserCareer m_user;
};




