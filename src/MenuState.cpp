#include "MenuState.h"
#include "Pictures.h"
#include "helpState.h"
#include "GetDataState.h"
#include <iostream>

MenuState::MenuState(MarioKart::GameDataRef data) :m_data(data),
                                                    m_helpState(false),
                                                    m_aboutState(false),
                                                    m_settingsState(false),
                                                    m_show_extra(false),
                                                    m_buttons()
{
}

void MenuState::Init()
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)windowSize.x / textureSize.x,
                          (float)windowSize.y / textureSize.y);



    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::about), false);
    m_buttons.back().first.setPosition(100, 440);
    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::help), false);
    m_buttons.back().first.setPosition(100, 300);
    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::letsPlay), false);
    m_buttons.back().first.setPosition(100, 200);
    m_buttons.emplace_back(Pictures::instance().getTexture(Pictures::settings), false);
    m_buttons.back().first.setPosition(100, 370);

    m_online.first.setTexture(Pictures::instance().getTexture(Pictures::online));
    m_career.first.setTexture(Pictures::instance().getTexture(Pictures::career));

    setposition();
}

void MenuState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseMoved)
    {
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });
        for( size_t i{ 0 }; i < 4; i++ )
        {
            if(m_buttons[ i ].first.getGlobalBounds().contains(location))
            {
                m_buttons[ i ].second = true;
                if( i == 2 )
                    m_show_extra = true;
            }
            else
                m_buttons[ i ].second = false;
        }

        if(m_online.first.getGlobalBounds().contains(location))
            m_online.second = true;
        if(m_career.first.getGlobalBounds().contains(location))
            m_career.second = true;

    }
    if (sf::Event::MouseMoved)
    {
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseMove.x, event.mouseMove.y });

        for( size_t i{ 0 }; i < 4; i++ )
        {
            if( m_buttons[ i ].first.getGlobalBounds().contains(location))
            {
                updateColors(i);
            }
        }

    }
}

void MenuState::updateColors(size_t cur_button)
{
    for( size_t i{ 0 }; i < 4; i++ )
    {
        if( i == cur_button )
            m_buttons[ i ].first.setColor(sf::Color(255, 255, 255, 130));
        else
            m_buttons[ i ].first.setColor(sf::Color(255, 255, 255, 250));
    }
}

void MenuState::Update(float dt)
{
    for( size_t i{ 0 }; i < 6; i++ )
    {
        switch( i )
        {
            case 0:
                break;
            case 1:
                if(m_buttons[1].second)
                    m_data->stateStack.AddState(StateStack::StateRef( new helpState(m_data)));
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                if(m_online.second)
                {
                    if(!m_data->user)
                        m_data->stateStack.AddState(StateStack::StateRef( new GetDataState(m_data)));
                    else
                        m_data->stateStack.AddState(StateStack::StateRef( new helpState(m_data)));
                }
                break;
            case 5:
                if(m_career.second)
                    m_data->stateStack.AddState(StateStack::StateRef( new helpState(m_data)));
                break;
        }
    }
}

void MenuState::Draw()
{
    m_data->window->draw(m_background);

    for( auto button : m_buttons )
        m_data->window->draw( button.first );

    if(m_show_extra)
    {
        m_data->window->draw(m_career.first);
        m_data->window->draw(m_online.first);
    }
}

void MenuState::setposition()
{
    m_online.first.setPosition(800, 220);
    m_career.first.setPosition(1100, 220);
}

