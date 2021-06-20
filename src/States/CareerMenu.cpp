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
#include "HostState.h"

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
    auto buttonCarer = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonCarer->setTextureInRect( 0, 485, 270, 60);
    buttonCarer->setInPosition(sf::Vector2f(150, 150));
    buttonCarer->setInScale(1.25, 1.5);

    // time title
    auto buttonTime = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonTime->setTextureInRect(0, 875, 453, 60);
    buttonTime->setInPosition(sf::Vector2f(150, 325));

    //collect coins
    auto buttonCollectionCoins = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonCollectionCoins->setTextureInRect(0, 955, 562, 57);
    buttonCollectionCoins->setInPosition(sf::Vector2f(150, 400));

    //dk
    auto buttonDK = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonDK->setTextureInRect(0, 795, 522, 66);
    buttonDK->setInPosition(sf::Vector2f(150, 475));

    //garage
    auto buttonGarage = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonGarage->setTextureInRect(520, 80, 280, 62);
    buttonGarage->setInPosition(sf::Vector2f(150, 550));
    buttonGarage->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new GarageState(m_data)), false);
    });

    //save
    auto buttonSave = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonSave->setTextureInRect(500, 0, 212, 54);
    buttonSave->setInPosition(sf::Vector2f(150, 625));
    buttonSave->setCallback(std::bind(&CareerMenu::saveUser, this));

    //back
    m_back->setCallback([this](){
        m_data->stateStack.RemoveState();
    });

    m_buttons[Options::Carer] = buttonCarer;
    m_buttons[Options::Time] = buttonTime;
    m_buttons[Options::CollectCoins] = buttonCollectionCoins;
    m_buttons[Options::DK] = buttonDK;
    m_buttons[Options::Garage] = buttonGarage;
    m_buttons[Options::Save] = buttonSave;
    m_buttons[Options::Back] = m_back;




    m_name = sf::Text(m_data->user.getName(),(Fonts::instance().Fonts::getFontMario()), 50);
    m_moneys = sf::Text((std::to_string(m_data->user.getCoins()) + "$"), (Fonts::instance().Fonts::getFontMario()), 50);
    std::string name = m_data->user.getSprite().substr(0, m_data->user.getSprite().find(".png"));
    m_car = sf::Text(name, (Fonts::instance().Fonts::getFontMario()), 50);
    m_name.setPosition(1000,100);
    m_name.setOutlineThickness(5.f);
	m_moneys.setPosition(1000,200);
    m_moneys.setOutlineThickness(5.f);
    m_car.setPosition(1000,300);
    m_car.setOutlineThickness(5.f);



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

        for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
        {
            if(auto res = it->second->validGlobalBound(location); res)
            {
                it->second->updateIfSelected(res);
                resetButtons(it->first);
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
        if(button.first != Options::Carer)
        {
            button.second->setFillInColor(255, 255, 255, 250);
            if(button.second->validGlobalBound(loc))
                button.second->setFillInColor(255, 255, 255, 130);
        }
    }
}


void CareerMenu::resetButtons(Options option)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        if(it->first != option)
            it->second->resetIfSelected();
    }
}

void CareerMenu::Update(float)
{
    setVolume(m_data->user.getIfSound());
    m_moneys.setString(std::to_string(m_data->user.getCoins()) + '$');

    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        switch (it->first)
        {
            case Options::Carer:
                break;
            case Options::Time:
                if(it->second->getIfSelected())
                    m_data->stateStack.AddState(StateStack::StateRef(new HostState(m_data, "TimeRace")), false);
                break;
            case Options::CollectCoins:
                if(it->second->getIfSelected())
                    m_data->stateStack.AddState(StateStack::StateRef(new HostState(m_data, "CoinRace")), false);
                break;
            case Options::DK:
                if(it->second->getIfSelected())
                    m_data->stateStack.AddState(StateStack::StateRef(new HostState(m_data, "DriftKingRace")), false);
                break;
            case Options::Garage:
                if(it->second->getIfSelected())
                    it->second->initCallback();
                break;
            case Options::Save:
                if (it->second->getIfSelected())
                    it->second->initCallback();
                break;
            case Options::Back:
                if(it->second->getIfSelected())
                    it->second->initCallback();
                break;
        }
       // it->second->resetIfSelected();
    }
}

void CareerMenu::Resume()
{
    for(auto& button : m_buttons)
        button.second->resetIfSelected();

    m_driverUser.setTexture(Pictures::instance().getTexture(m_data->user.getSprite()));

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
        m_data->window->draw(*it.second.get());

}

void CareerMenu::saveUser()
{
    std::fstream file;

    remove("save.txt");
    std::ofstream("save.txt");


    file.open("save.txt");
    if (file.fail())
        throw std::runtime_error("Error: file not found/exist\n");

    file << m_data->user.getName() << "\n";
    file << m_data->user.getCoins() << "\n";
    file << m_data->user.getMapGame() << "\n";
    for (int i = 0; i < m_data->user.getMaxDrivers(); ++i)
        file << m_data->user.getDrive(i) << "\n";

    file.close();
    m_buttons[Options::Save]->resetIfSelected();
}



