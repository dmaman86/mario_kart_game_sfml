#include <CareerMenu.h>
#include"CareerState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "GetDataState.h"
#include "Macros.h"
#include <iostream>
#include <fstream>
#include <filesystem>

//========================== Constructor / Destructor =========================
CareerState::CareerState(MarioKart::GameDataRef& data):
    m_data(data),
    StateOfMenu(data),
    m_buttons()
{
    m_soundOn = m_data->user.getIfSound();
}
//=============================================================================
void CareerState::Init()
{
    auto buttonNewGame = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonNewGame->setTextureInRect(PositionButtons::newGame);
    buttonNewGame->setInOrigin();
    buttonNewGame->setInPosition(sf::Vector2f(m_windowSize.x / 2.f, m_windowSize.y / 2.f));
    buttonNewGame->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)),false);
    });
    auto buttonLoadGame = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonLoadGame->setTextureInRect(PositionButtons::loadGame);
    buttonLoadGame->setInOrigin();
    buttonLoadGame->setInPosition(sf::Vector2f(m_windowSize.x / 2.f, (m_windowSize.y / 2.f) + 100));
    buttonLoadGame->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new CareerMenu(m_data)),false);
    });
    m_back->setCallback([this](){
       m_data->stateStack.RemoveState();
    });

    m_buttons[Options::NewGame] = buttonNewGame;
    m_buttons[Options::LoadGame] = buttonLoadGame;
    m_buttons[Options::Back] = m_back;
}
//=============================================================================
void CareerState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
        if(m_soundOn)
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });

        for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
        {
            auto& button = it->second;
            if( auto res = button->validGlobalBound(location); res)
            {
                button->updateIfSelected(res);
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
//=============================================================================
void CareerState::resetButtons(Options option)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        if(it->first != option)
            it->second->resetIfSelected();
    }
}
//=============================================================================
void CareerState::Update(const float)
{
    setVolume(m_data->user.getIfSound());

    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        switch (it->first)
        {
            case Options::NewGame:
                if (it->second->getIfSelected())//if pres new game
                    it->second->initCallback();
                break;
            case Options::LoadGame:
                if (it->second->getIfSelected())//if pres load game
                {
                    if (openLoadFile())
                    {
                        it->second->initCallback();
                    }
                }
                break;
            case Options::Back:
                if (it->second->getIfSelected())//if pres back
                    it->second->initCallback();
                break;
        }
    }
}
//=============================================================================
void CareerState::Resume()
{
    for (auto& button : m_buttons)
        button.second->resetIfSelected();
}

void CareerState::Draw()
{
	m_data->window->draw(m_background);
    m_data->window->draw(m_logo);

    for (auto it : m_buttons)
        m_data->window->draw(*it.second.get());
}

//=============================================================================
const bool CareerState::openLoadFile()
{
    //If the file does not exist
    if (std::filesystem::exists("save.txt"))
    {
        std::string line_text;

        std::ifstream loadGame;
        try{
            loadGame.open("save.txt");
            if (loadGame.fail())
                throw std::runtime_error("Error: file not found/exist\n");
        }catch(...){
            return false;
        }

        //get name
        std::getline(loadGame, line_text);
        m_data->user.setName(line_text);
        //get number coins
        std::getline(loadGame, line_text);
        m_data->user.setCoins(std::stoi(line_text));

        //take all the cars
        while (loadGame.peek() != std::ifstream::traits_type::eof())
        {
            std::getline(loadGame, line_text);
            m_data->user.setDrive(line_text);
        }

        //get first driver 
        m_data->user.setSprite(m_data->user.getDrive(0));

        loadGame.close();
        return true;
    }
    m_buttons[Options::LoadGame]->resetIfSelected();
    return false;
}

//Color change when you move the mouse with the button
//=============================================================================
void CareerState::updateColors(const sf::Vector2f& loc)
{
    for (auto &it : m_buttons)
    {
        
        it.second->setFillInColor(Color::REGULARCOLOR);
        if (it.second->validGlobalBound(loc))
            it.second->setFillInColor(Color::TRANSPARENCYCOLOR);
    }
}