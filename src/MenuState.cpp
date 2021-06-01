#include "MenuState.h"
#include "Pictures.h"
#include "helpState.h"
#include <iostream>

MenuState::MenuState(MarioKart::GameDataRef data) :m_data(data), m_helpState(false), m_aboutState(false), m_settingsState(false)
{
}

void MenuState::Init()
{
    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_about.setTexture(Pictures::instance().getTexture(Pictures::about));
    m_help.setTexture(Pictures::instance().getTexture(Pictures::help));
    m_letsPlay.setTexture(Pictures::instance().getTexture(Pictures::letsPlay));
    m_settings.setTexture(Pictures::instance().getTexture(Pictures::settings));
    setposition();
}

void MenuState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseMoved) {
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });
        if (m_letsPlay.getGlobalBounds().contains(location)) {
            m_online.setTexture(Pictures::instance().getTexture(Pictures::online));
            m_career.setTexture(Pictures::instance().getTexture(Pictures::career));
        }
        else if(m_help.getGlobalBounds().contains(location)) {
            m_helpState = true;
        }

    }
    if (sf::Event::MouseMoved) {
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseMove.x, event.mouseMove.y });

        if (m_letsPlay.getGlobalBounds().contains(location)) {
            m_letsPlay.setColor(sf::Color(255, 255, 255, 130));
            m_help.setColor(sf::Color(255, 255, 255, 250));
            m_about.setColor(sf::Color(255, 255, 255, 250));
            m_settings.setColor(sf::Color(255, 255, 255, 250));
        }
        else if(m_help.getGlobalBounds().contains(location)) {
            m_help.setColor(sf::Color(255, 255, 255, 130));
            m_letsPlay.setColor(sf::Color(255, 255, 255, 250));
            m_about.setColor(sf::Color(255, 255, 255, 250));
            m_settings.setColor(sf::Color(255, 255, 255, 250));
        }
        else if(m_about.getGlobalBounds().contains(location)) {
            m_about.setColor(sf::Color(255, 255, 255, 130));
            m_letsPlay.setColor(sf::Color(255, 255, 255, 250));
            m_help.setColor(sf::Color(255, 255, 255, 250));
            m_settings.setColor(sf::Color(255, 255, 255, 250));
        }
        else if(m_settings.getGlobalBounds().contains(location)) {
            m_settings.setColor(sf::Color(255, 255, 255, 130));
            m_letsPlay.setColor(sf::Color(255, 255, 255, 250));
            m_help.setColor(sf::Color(255, 255, 255, 250));
            m_about.setColor(sf::Color(255, 255, 255, 250));
        }
        else
        {
            m_settings.setColor(sf::Color(255, 255, 255, 250));
            m_letsPlay.setColor(sf::Color(255, 255, 255, 250));
            m_help.setColor(sf::Color(255, 255, 255, 250));
            m_about.setColor(sf::Color(255, 255, 255, 250));
        }

    }
}

void MenuState::Update(float)
{
    if (m_helpState)
        m_data->stateStack.AddState(StateStack::StateRef(new helpState(m_data)), true);
}

void MenuState::Draw()
{
    m_data->window->draw(m_background);
    m_data->window->draw(m_about);
    m_data->window->draw(m_help);
    m_data->window->draw(m_letsPlay);
    m_data->window->draw(m_online);
    m_data->window->draw(m_career);
    m_data->window->draw(m_settings);

}

void MenuState::setposition()
{
    m_letsPlay.setPosition(100,200);
    m_help.setPosition(100, 300);
    m_settings.setPosition(100, 370);
    m_about.setPosition(100, 440);
    m_online.setPosition(800, 220);
    m_career.setPosition(1100, 220);
}

