#include <CareerMenu.h>
#include"CareerState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "GetDataState.h"



CareerState::CareerState(MarioKart::GameDataRef& data): m_data(data), m_user()
{
    InitOfMenu(m_data);
}

void CareerState::Init()
{
  
    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//new game
    m_buttons.back().first.setTextureRect(sf::Rect(0, 75, 405, 66));
    m_buttons.back().first.setPosition((float)m_windowSize.x / 2.5, (float)m_windowSize.y / 2.5);
    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//load game
    m_buttons.back().first.setTextureRect(sf::Rect(0, 160, 428, 67));
    m_buttons.back().first.setPosition((float)m_windowSize.x / 2.5, (float)m_windowSize.y / 2.5 + 100);
    m_buttons.emplace_back(m_back,false);

}

void CareerState::HandleEvent(const sf::Event& event)
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

void CareerState::Update(float)
{
    setVolume(m_data->user.getIfSound());
 
    for (size_t i{ 0 }; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            if (m_buttons[0].second)//if pres new game
                m_data->stateStack.AddState(StateStack::StateRef(new CareerMenu(m_data, m_user)),false);

            break;
        case 1:
            if (m_buttons[1].second)//if pres load game
            {
                openLoadFile();
                m_data->stateStack.AddState(StateStack::StateRef(new CareerMenu(m_data, m_user)),false);
            }
            break;
        case 2:
            if (m_buttons[2].second)//if pres back
                m_data->stateStack.RemoveState();

            break;
        }
    }
}

void CareerState::Resume()
{
    for(auto& button : m_buttons)
        button.second = false;
}

void CareerState::Draw()
{
	m_data->window->draw(m_background);

    for (auto it : m_buttons)
        m_data->window->draw(it.first);
}

void CareerState::openLoadFile()
{
    std::string line_text;
    std::string line;

    std::ifstream loadGame;
    loadGame.open("load.txt");
    if(loadGame.fail())
        throw std::runtime_error("Error: loadGame not found/exist\n");

    std::getline(loadGame, line_text);
    m_user.setName(line_text);
    std::getline(loadGame, line_text);
    m_user.setCoins(std::stoi(line_text));

    while (loadGame.peek() != std::ifstream::traits_type::eof())
    {
        std::getline(loadGame, line_text);
        m_user.setCar(line_text);
    }

    loadGame.close();
}

