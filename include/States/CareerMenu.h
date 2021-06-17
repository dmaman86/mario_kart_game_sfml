#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    void saveUser();
    void resetButtons(size_t);

    sf::Sprite m_driver;
    sf::Text m_name;
    sf::Text m_moneys;
    sf::Text m_car;
    MarioKart::GameDataRef m_data;
    sf::Sprite m_driverUser;
    std::vector< Button > m_buttons;
};




