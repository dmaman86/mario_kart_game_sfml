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
#include "Macros.h"

const sf::Vector2f CARERPOS(150, 150);
const sf::Vector2f TIMEPOS(150, 325);
const sf::Vector2f COLLECTPOS(150, 400);
const sf::Vector2f DKPOS(150, 475);
const sf::Vector2f GARAGEPOS(150,550);
const sf::Vector2f SAVEPOS(150, 625);
const sf::Vector2f NAMEPOS(1000, 100);
const sf::Vector2f MONEYSPOS(1000, 200);
const sf::Vector2f CARPOS(1000, 300);
const sf::Vector2f DRIVERUSER(1000,500);
const sf::Vector2f RECPOS(990, 450);



const sf::Vector2f SCALECAR(10, 8);
const sf::Vector2f SIZEREC(300, 300);
const sf::Rect SIZEDRAIVER(355, 33, 30, 30);


//========================== Constructor / Destructor =========================
CareerMenu::CareerMenu(MarioKart::GameDataRef& data): m_data(data),
                                                        StateOfMenu(data),
                                                        m_buttons(),
                                                        m_driverUser(),
                                                        m_rect(), 
                                                        m_title()
{
    
    m_soundOn = m_data->user.getIfSound();
}
//=============================================================================
void CareerMenu::Init()
{
    // carrer title
    auto buttonCarer = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonCarer->setTextureInRect(PositionButtons::carerTitle);
    buttonCarer->setInPosition(CARERPOS);
    buttonCarer->setInScale(1.25, 1.5);

    // time title
    auto buttonTime = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonTime->setTextureInRect(PositionButtons::timeRace);
    buttonTime->setInPosition(TIMEPOS);

    //collect coins
    auto buttonCollectionCoins = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonCollectionCoins->setTextureInRect(PositionButtons::collectionCoinsRace);
    buttonCollectionCoins->setInPosition(COLLECTPOS);

    //dk
    auto buttonDK = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonDK->setTextureInRect(PositionButtons::dkRace);
    buttonDK->setInPosition(DKPOS);

    //garage
    auto buttonGarage = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonGarage->setTextureInRect(PositionButtons::garage);
    buttonGarage->setInPosition(GARAGEPOS);
    buttonGarage->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new GarageState(m_data)), false);
    });

    //save
    auto buttonSave = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonSave->setTextureInRect(PositionButtons::save);
    buttonSave->setInPosition(SAVEPOS);
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

    m_name = sf::Text(m_data->user.getName(),(Fonts::instance().Fonts::getFontMario()), SIZETEXT);
    m_moneys = sf::Text((std::to_string(m_data->user.getCoins()) + "$"), (Fonts::instance().Fonts::getFontMario()), SIZETEXT);
    std::string name = m_data->user.getSprite().substr(0, m_data->user.getSprite().find(".png"));
    m_car = sf::Text(name, (Fonts::instance().Fonts::getFontMario()), SIZETEXT);
    m_name.setPosition(NAMEPOS);
    m_name.setOutlineThickness(THICK);
	m_moneys.setPosition(MONEYSPOS);
    m_moneys.setOutlineThickness(THICK);
    m_car.setPosition(CARPOS);
    m_car.setOutlineThickness(THICK);

    m_driverUser.setTexture(Pictures::instance().getTexture(m_data->user.getSprite()));
    m_driverUser.setTextureRect(SIZEDRAIVER);
    m_driverUser.scale(SCALECAR);
    m_driverUser.setPosition(DRIVERUSER);

    m_rect.setFillColor(Color::GRAYCOLOR);
    m_rect.setSize(SIZEREC);
    m_rect.setOutlineColor(sf::Color::Green);
    m_rect.setOutlineThickness(5);
    m_rect.setPosition(RECPOS);
}
//=============================================================================
void CareerMenu::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        if(m_soundOn)
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

//Color change when you move the mouse with the button
//=============================================================================
void CareerMenu::updateColors(const sf::Vector2f loc)
{
    for (auto& button : m_buttons)
    {
        if(button.first != Options::Carer)
        {
            button.second->setFillInColor(Color::REGULARCOLOR);
            if(button.second->validGlobalBound(loc))
                button.second->setFillInColor(Color::TRANSPARENCYCOLOR);
        }
    }
}

//=============================================================================
void CareerMenu::resetButtons(Options option)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        if(it->first != option)
            it->second->resetIfSelected();
    }
}


//=============================================================================
void CareerMenu::Update(const float)
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
    }
}
//If we went back to this page
//=============================================================================
void CareerMenu::Resume()
{
    for(auto& button : m_buttons)
        button.second->resetIfSelected();

    m_driverUser.setTexture(Pictures::instance().getTexture(m_data->user.getSprite()));

}
//=============================================================================
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
    m_data->window->draw(m_logo);

    for (auto it : m_buttons)
        m_data->window->draw(*it.second.get());

}
//If you click Save
//=============================================================================
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



