#include "CareerMenu.h"
#include "Pictures.h"
#include "MenuState.h"
#include "GetDataState.h"
#include "Fonts.h"
#include <string>
#include "RaceStatesBase.h"
#include <iostream>
#include <fstream>
#include <filesystem>

CareerMenu::CareerMenu(MarioKart::GameDataRef& data): m_data(data),
                                                        StateOfMenu(data),
                                                        m_buttons()
{

}

void CareerMenu::Init()
{
    m_buttons.emplace_back(Button(Pictures::MenuButtons1));
    m_buttons.back().setTextureInRect(0, 485, 270, 60);
    m_buttons.back().setInPosition(sf::Vector2f(150, 150));
    m_buttons.back().setIntoScale(1.25, 1.25);

    m_buttons.emplace_back(Pictures::MenuButtons1);
    m_buttons.back().setTextureInRect(0, 875, 453, 60);
    m_buttons.back().setInPosition(sf::Vector2f(150, 325));


    m_buttons.emplace_back(Pictures::MenuButtons1);//collect coins
    m_buttons.back().setTextureInRect(0, 955, 562, 57);
    m_buttons.back().setInPosition(sf::Vector2f(150, 400));

    m_buttons.emplace_back(Pictures::MenuButtons1);//dk
    m_buttons.back().setTextureInRect(0, 795, 522, 66);
    m_buttons.back().setInPosition(sf::Vector2f(150, 475));

    m_buttons.emplace_back(Pictures::MenuButtons1);//garage
    m_buttons.back().setTextureInRect(520, 80, 280, 62);
    m_buttons.back().setInPosition(sf::Vector2f(150, 550));

    m_buttons.emplace_back(Pictures::MenuButtons1);//save
    m_buttons.back().setTextureInRect(500, 0, 212, 54);
    m_buttons.back().setInPosition(sf::Vector2f(150, 625));

    m_buttons.emplace_back(m_back);//back

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

    m_name.setString(m_data->user.getName());
    m_moneys.setString(std::to_string(m_data->user.getCoins()) + "$");
    m_car.setString("Mario Mother fucker");


    m_name.setPosition(1000,100);
    m_name.setFillColor(sf::Color::Black);
    m_name.setScale(1.5, 1.5);
    m_moneys.setPosition(1000,200);
    m_moneys.setFillColor(sf::Color::Black);
    m_moneys.setScale(1.5, 1.5);

    m_car.setPosition(1000,300);
    m_car.setFillColor(sf::Color::Black);
}

void CareerMenu::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });

        for(size_t i{0}; i < m_buttons.size(); i++)
        {
            auto& button = m_buttons[ i ];
            if(auto res = button.validGlobalBound(location); res)
            {
                button.updateIfSelected(res);
                resetButtons(i);
                break;
            }
        }
    }
}

void CareerMenu::resetButtons(size_t index )
{
    for(size_t i{ 0 }; i < m_buttons.size(); i++)
    {
        if(i != index)
            m_buttons[ i ].resetIfSelected();
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
            if (m_buttons[1].getIfSelected())//if pres time race
                m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
            break;
        case 2:
            if (m_buttons[2].getIfSelected())//if pres collect coins race
                m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
            break;

        case 3:
            if (m_buttons[3].getIfSelected())//if pres dk race
                m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
            break;

        case 4:
            if (m_buttons[4].getIfSelected())//if pres back
            { }
                break;
        case 5:
            if (m_buttons[5].getIfSelected())//if pres back
                saveUser();
            break;
        case 6:
            if (m_buttons[6].getIfSelected())//if pres back
                m_data->stateStack.RemoveState();

            break;
        }
    }
}

void CareerMenu::Resume()
{
    for(auto& button : m_buttons)
        button.resetIfSelected();
}

void CareerMenu::Draw()
{

    m_data->window->draw(m_background);
    m_data->window->draw(m_driver);
    m_data->window->draw(m_name);
    m_data->window->draw(m_moneys);
    m_data->window->draw(m_car);

    for (auto it : m_buttons)
        it.draw(m_data->window);

}

void CareerMenu::saveUser()
{
    std::fstream file;
    //std::fstream  ofs;


    //ofs.open("load.txt", std::ios::out | std::ios::trunc);
    //if (ofs.fail())
    //    throw std::runtime_error("Error: loadGame not found/exist\n");

    // ofs << "dfsdgsdg";
    //// //std::getline(loadGame, line_text);
    //// //m_user.setName(line_text);
    //// //std::getline(loadGame, line_text);
    //// //m_user.setCoins(std::stoi(line_text));

    // //while (loadGame.peek() != std::ifstream::traits_type::eof())
    // //{
    // //    std::getline(loadGame, line_text);
    // //    m_user.setCar(line_text);
    // //}

    //ofs.close();
    //m_buttons[5].second = false;

    remove("save.txt");

    std::ofstream ("save.txt");

    file.open("save.txt");
    file << "Writing this to a file.\n";
    file.close();
    m_buttons[5].resetIfSelected();

}



