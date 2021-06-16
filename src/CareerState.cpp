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
    StateOfMenu(data)
{

}

void CareerState::Init()
{
    m_buttons.emplace_back(Pictures::MenuButtons1);
    m_buttons.back().setTextureInRect(0, 75, 405, 66);
    m_buttons.back().setInPosition(sf::Vector2f(m_windowSize.x / 2.5f, m_windowSize.y / 2.5));
    m_buttons.back().setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new CareerMenu(m_data)),false);
    });
    m_buttons.emplace_back(Pictures::MenuButtons1);
    m_buttons.back().setTextureInRect(0, 160, 428, 67);
    m_buttons.back().setInPosition(sf::Vector2f(m_windowSize.x / 2.5, m_windowSize.y / 2.5 + 100));
    m_buttons.back().setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new CareerMenu(m_data)),false);
    });
    m_buttons.emplace_back(m_back);
    m_buttons.back().setCallback([this](){
        m_data->stateStack.RemoveState();
    });
}

void CareerState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });

        for(size_t i{0}; i < m_buttons.size(); i++)
        {
            if( auto res = m_buttons[ i ].validGlobalBound(location); res)
            {
                m_buttons[ i ].updateIfSelected(res);
                resetButtons(i);
                break;
            }
        }
    }
}

void CareerState::resetButtons(size_t index)
{
    for(size_t i{0}; i < m_buttons.size(); i++)
    {
        if( i != index)
            m_buttons[ i ].resetIfSelected();
    }
}

void CareerState::Update(float)
{
    setVolume(m_data->user.getIfSound());
 
    for (size_t i{ 0 }; i < m_buttons.size(); i++)
    {
        switch (i)
        {
            case 0:
            {
                if (m_buttons[0].getIfSelected())//if pres new game
                    m_buttons[0].initCallback();
                break;
            }
            case 1:
            {
                if (m_buttons[1].getIfSelected())//if pres load game
                {
                    if(openLoadFile())
                        m_buttons[1].initCallback();
                }
                break;
            }
            case 2:
            {
                if (m_buttons[2].getIfSelected())//if pres back
                    m_buttons[2].initCallback();
                break;
            }
        }
    }
}

void CareerState::Resume()
{
    for(auto& button : m_buttons)
        button.resetIfSelected();
}

void CareerState::Draw()
{
	m_data->window->draw(m_background);

    for (auto it : m_buttons)
        it.draw(m_data->window);
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
        // m_user.setCoins(std::stoi(line_text));

        while (loadGame.peek() != std::ifstream::traits_type::eof())
        {
            std::getline(loadGame, line_text);
            m_data->user.setCar(line_text);
        }

        loadGame.close();
        return true;
    }
    m_buttons[1].resetIfSelected();
    return false;
}

