#include "CareerMenu.h"
#include "Pictures.h"
#include "MenuState.h"
#include "GetDataState.h"
#include "Fonts.h"
#include <string>
#include "RaceStatesBase.h"
CareerMenu::CareerMenu(MarioKart::GameDataRef& data, UserCareer& user): m_data(data),
                                                                        m_user(user)
{
    InitOfMenu(m_data);

}

void CareerMenu::Init()
{

   

    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//carrer
    m_buttons.back().first.setTextureRect(sf::Rect(0, 485, 270, 60));
    m_buttons.back().first.setPosition(150, 150);
    m_buttons.back().first.setScale(1.25,1.25);

    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//time
    m_buttons.back().first.setTextureRect(sf::Rect(0, 875, 453, 60));
    m_buttons.back().first.setPosition(150, 325);

    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//collect coins
    m_buttons.back().first.setTextureRect(sf::Rect(0, 955, 562, 57));
    m_buttons.back().first.setPosition(150, 400);

    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//dk
    m_buttons.back().first.setTextureRect(sf::Rect(0, 795, 522, 66));
    m_buttons.back().first.setPosition(150, 475);

    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//garage
    m_buttons.back().first.setTextureRect(sf::Rect(520, 80, 280, 62));
    m_buttons.back().first.setPosition(150, 550);

    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//save
    m_buttons.back().first.setTextureRect(sf::Rect(500, 0, 212, 54));
    m_buttons.back().first.setPosition(150, 625);

    m_buttons.emplace_back(m_back, false);//back

    //m_drivers.emplace_back(Pictures::MarioDriver, Pictures::instance().getTexture(Pictures::MarioDriver));

  /* m_driver.setTexture(Pictures::instance().getTexture(m_user.getDrivers()));
   m_driver.setTextureRect(sf::Rect(95, 0, 33, 30));
   m_driver.setOrigin(m_driver.getGlobalBounds().width/2,m_driver.getGlobalBounds().height/2);
   m_driver.scale(8,8);
   m_driver.setPosition(1100,500);*/



    //m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));

    m_name.setFont(Fonts::instance().Fonts::getFontMario());
    m_moneys.setFont(Fonts::instance().Fonts::getFontMario());
    m_car.setFont(Fonts::instance().Fonts::getFontMario());

    m_name.setString(m_user.getName());
    m_moneys.setString(std::to_string(m_user.getCoins()) + "$");
    m_car.setString("Mario Mother fucker");


    m_name.setPosition(1000,100);
    m_name.setColor(sf::Color::Black);
    m_name.setScale(1.5, 1.5);
    m_moneys.setPosition(1000,200);
    m_moneys.setColor(sf::Color::Black);
    m_moneys.setScale(1.5, 1.5);

    m_car.setPosition(1000,300);
    m_car.setColor(sf::Color::Black);
}

void CareerMenu::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });
      
        for (auto& button : m_buttons)
        {
            if (button.first.getGlobalBounds().contains(location))
                button.second = true;
            else
                button.second = false;
        }
    }
}

void CareerMenu::Update(float)
{
    setVolume(m_data->user.getIfSound());

    for (size_t i{ 1 }; i < 7; i++)
    {
        switch (i)
        {
        case 1:
            if (m_buttons[1].second)//if pres time race
                m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
            break;
        case 2:
            if (m_buttons[2].second)//if pres collect coins race
                m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
            break;

        case 3:
            if (m_buttons[3].second)//if pres dk race
                m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
            break;

        case 4:
            if (m_buttons[4].second)//if pres back
            { }
                break;
        case 5:
            if (m_buttons[5].second)//if pres back
                saveUser();
            break;
        case 6:
            if (m_buttons[6].second)//if pres back
                m_data->stateStack.RemoveState();

            break;
        }
    }




}

void CareerMenu::Draw()
{

    m_data->window->draw(m_background);
    m_data->window->draw(m_driver);
    m_data->window->draw(m_name);
    m_data->window->draw(m_moneys);
    m_data->window->draw(m_car);

    for (auto it : m_buttons)
        m_data->window->draw(it.first);

}

void CareerMenu::saveUser()
{

}



