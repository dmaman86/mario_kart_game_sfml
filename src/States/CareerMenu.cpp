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
#include "TimeRace.h"
#include "GarageState.h"
#include "CoinRace.h"
#include "DriftKingRace.h"

CareerMenu::CareerMenu(MarioKart::GameDataRef& data): m_data(data),
                                                        StateOfMenu(data),
                                                        m_buttons(),
                                                        m_driverUser(),
                                                        m_rect(), 
                                                        m_title()
{
    

}

void CareerMenu::Init()
{
    // carrer title
    m_title.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons1));
    m_title.setTextureRect(sf::Rect( 0, 485, 270, 60));
    m_title.setPosition(sf::Vector2f(150, 150));
    m_title.setScale(1.25,1.5);


    // time title
    m_buttons.emplace_back(Pictures::MenuButtons1);
    m_buttons.back().setTextureInRect(0, 875, 453, 60);
    m_buttons.back().setInPosition(sf::Vector2f(150, 325));
    m_buttons.back().setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new TimeRace(m_data)), false);
    });

    //collect coins
    m_buttons.emplace_back(Pictures::MenuButtons1);
    m_buttons.back().setTextureInRect(0, 955, 562, 57);
    m_buttons.back().setInPosition(sf::Vector2f(150, 400));
    m_buttons.back().setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new CoinRace(m_data)), false);
    });

    //dk
    m_buttons.emplace_back(Pictures::MenuButtons1);
    m_buttons.back().setTextureInRect(0, 795, 522, 66);
    m_buttons.back().setInPosition(sf::Vector2f(150, 475));
    m_buttons.back().setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new DriftKingRace(m_data)), false);
    });

    //garage
    m_buttons.emplace_back(Pictures::MenuButtons1);
    m_buttons.back().setTextureInRect(520, 80, 280, 62);
    m_buttons.back().setInPosition(sf::Vector2f(150, 550));
    m_buttons.back().setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new GarageState(m_data)), false);
    });

    //save
    m_buttons.emplace_back(Pictures::MenuButtons1);
    m_buttons.back().setTextureInRect(500, 0, 212, 54);
    m_buttons.back().setInPosition(sf::Vector2f(150, 625));

    //back
    m_buttons.emplace_back(m_back);
    m_buttons.back().setCallback([this](){
        m_data->stateStack.RemoveState();
    });

    m_name.setFont(Fonts::instance().Fonts::getFontMario());
    m_moneys.setFont(Fonts::instance().Fonts::getFontMario());
    m_car.setFont(Fonts::instance().Fonts::getFontMario());

    m_name.setString(m_data->user.getName());
    m_moneys.setString(std::to_string(m_data->user.getCoins()) + "$");
    std::string name = m_data->user.getSprite().substr(0, m_data->user.getSprite().find(".png"));

    m_car.setString(name);


    m_name.setPosition(1000,100);
    m_name.setFillColor(sf::Color::Black);
    m_name.setScale(1.5, 1.5);
	m_moneys.setPosition(1000,200);
    m_moneys.setFillColor(sf::Color::Black);
    m_moneys.setScale(1.5, 1.5);


    m_car.setPosition(1000,300);
    m_car.setFillColor(sf::Color::Black);

    m_driverUser.setTexture(Pictures::instance().getTexture(m_data->user.getSprite()));
    m_driverUser.setTextureRect(sf::Rect(355, 33, 30, 30));
    m_driverUser.scale(10, 8);
    m_driverUser.setPosition(1000, 500);

    m_rect.setFillColor(sf::Color(0, 0, 0, 100));
    m_rect.setSize(sf::Vector2f(300, 300));
    m_rect.setOutlineColor(sf::Color::Red);
    m_rect.setOutlineThickness(5);
    m_rect.setPosition(990, 450);
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
    if (sf::Event::MouseMoved == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseMove.x, event.mouseMove.y });

        updateColors(location);

    }
}

void CareerMenu::updateColors(const sf::Vector2f loc)
{
    for (auto& button : m_buttons)
    {
        button.setFillInColor(255, 255, 255, 250);
        if (button.validGlobalBound(loc))
            button.setFillInColor(255, 255, 255, 130);
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
    m_moneys.setString(std::to_string(m_data->user.getCoins()) + '$');

    for (size_t i{ 1 }; i < 7; i++)
    {
        switch (i)
        {
        case 1://if pres time race
            if (m_buttons[0].getIfSelected())
                m_buttons[0].initCallback();
            break;
        case 2://if pres collect coins race
            if (m_buttons[1].getIfSelected())
                m_buttons[1].initCallback();
            break;

        case 3://if pres dk race
            if (m_buttons[2].getIfSelected())
                m_buttons[2].initCallback();
            break;

        case 4: // if press garage state
            if (m_buttons[3].getIfSelected())
                m_buttons[3].initCallback();
                break;
        case 5: // if save press
            if (m_buttons[4].getIfSelected())
                saveUser();
            break;
        case 6://if pres back
            if (m_buttons[5].getIfSelected())
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
    m_data->window->draw(m_title);
    m_data->window->draw(m_driver);
    m_data->window->draw(m_name);
    m_data->window->draw(m_moneys);
    m_data->window->draw(m_car);
    m_data->window->draw(m_rect);
    m_data->window->draw(m_driverUser);

    for (auto it : m_buttons)
        m_data->window->draw(it);

}

void CareerMenu::saveUser()
{
    std::fstream file;

    remove("save.txt");
    std::ofstream("save.txt");


    file.open("save.txt");
    file << m_data->user.getName() << "\n";
    file << m_data->user.getCoins() << "\n";
    file << m_data->user.getSprite() << "\n";

    file.close();
    m_buttons[5].resetIfSelected();

}



