#include <CareerMenu.h>
#include"CareerState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "GetDataState.h"
#include <iostream>
#include <fstream>
#include <filesystem>


CareerState::CareerState(MarioKart::GameDataRef& data):
    m_data(data),
    StateOfMenu(data),
    m_buttons()
{

}

void CareerState::Init()
{
    auto buttonNewGame = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonNewGame->setTextureInRect(0, 75, 405, 66);
    buttonNewGame->setInPosition(sf::Vector2f(m_windowSize.x / 2.5f, m_windowSize.y / 2.5));
    buttonNewGame->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)),false);
    });
    auto buttonLoadGame = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonLoadGame->setTextureInRect(0, 160, 428, 67);
    buttonLoadGame->setInPosition(sf::Vector2f(m_windowSize.x / 2.5, m_windowSize.y / 2.5 + 100));
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

void CareerState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
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
}

void CareerState::resetButtons(Options option)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        if(it->first != option)
            it->second->resetIfSelected();
    }
}

void CareerState::Update(float)
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
                    if(openLoadFile())
                        it->second->initCallback();
                }
                break;
            case Options::Back:
                if (it->second->getIfSelected())//if pres back
                    it->second->initCallback();
                break;
        }
    }
}

void CareerState::Resume()
{
    for (auto& button : m_buttons)
        button.second->resetIfSelected();
}

void CareerState::Draw()
{
	m_data->window->draw(m_background);

    for (auto it : m_buttons)
        m_data->window->draw(*it.second.get());
}

bool CareerState::openLoadFile()
{
    if (std::filesystem::exists("save.txt"))
    {
        std::string line_text;
        std::string line;

        std::ifstream loadGame;
        loadGame.open("save.txt");
        if (loadGame.fail())
            throw std::runtime_error("Error: loadGame not found/exist\n");

        std::getline(loadGame, line_text);
        m_data->user.setName(line_text);
        std::getline(loadGame, line_text);
        m_data->user.setCoins(std::stoi(line_text));
        std::getline(loadGame, line_text);
        m_data->user.setMapGame(line_text);

        while (loadGame.peek() != std::ifstream::traits_type::eof())
        {
            std::getline(loadGame, line_text);
            m_data->user.setDrive(line_text);
        }

        m_data->user.setSprite(m_data->user.getDrive(0));

        loadGame.close();
        return true;
    }
    m_buttons[Options::LoadGame]->resetIfSelected();
    return false;
}