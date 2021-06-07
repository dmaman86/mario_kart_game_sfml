#include "MenuState.h"
#include "Pictures.h"
#include "helpState.h"
#include "GetDataState.h"
#include "SettingsState.h"
#include <iostream>


MenuState::MenuState(MarioKart::GameDataRef& data) :m_data(data),
                                                    m_buttons(),
                                                    m_showExtra(false),
                                                    m_online(Pictures::instance().getTexture(Pictures::online), false),
                                                    m_carrer(Pictures::instance().getTexture(Pictures::career), false)
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

    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));

    m_startMusic.openFromFile(Sounds::menu);
    m_startMusic.setLoop(true);
    m_startMusic.play();
    setposition();
	
	m_buttons.push_back(m_online);
	m_buttons.push_back(m_carrer);
}

void MenuState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });

        for( auto & button:m_buttons)
        {
            if(button.first.getGlobalBounds().contains(location))
				button.second = true;
            else
				button.second = false;
        }

       // if(m_online.first.getGlobalBounds().contains(location))
        //    m_online.second = true;
        //if(m_carrer.first.getGlobalBounds().contains(location))
         //   m_carrer.second = true;
    }
    if (sf::Event::MouseMoved == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseMove.x, event.mouseMove.y });

		updateColors(location);
    }
}

void MenuState::updateColors(const sf::Vector2f loc)
{
	for (auto & button : m_buttons)
	{
		button.first.setColor(sf::Color(255, 255, 255, 250));

		if (button.first.getGlobalBounds().contains(loc))
			button.first.setColor(sf::Color(255, 255, 255, 130));
	}
}

void MenuState::Update(float dt)
{

    for( size_t i{ 0 }; i < 6; i++ )
    {
        switch( i )
        {
            case 0:
                // state about
                break;
            case 1:
                if(m_buttons[1].second)
                    m_data->stateStack.AddState(StateStack::StateRef( new helpState(m_data)), false);
                break;
            case 2:
				if (m_buttons[2].second)
				m_showExtra = true;
                /*if(m_buttons[2].second)
                    m_data->stateStack.AddState(StateStack::StateRef( new GetDataState(m_data)), false);*/
                break;
            case 3:
                if (m_buttons[3].second)
                    m_data->stateStack.AddState(StateStack::StateRef(new SettingsState(m_data, m_startMusic)), false);
                break;
            case 4:
                if(m_buttons[4].second)
                    m_data->stateStack.AddState(StateStack::StateRef( new GetDataState(m_data)), false);
                break;
            case 5:
				if (m_buttons[5].second)
                    m_data->stateStack.AddState(StateStack::StateRef( new helpState(m_data)), false);
                break;
        }
    }
}

void MenuState::Draw()
{
	m_data->window->draw(m_background);

	for (auto it = m_buttons.begin();
		 (m_showExtra) ? it != m_buttons.cend() : it != m_buttons.cend() - 2 ; it++)
		m_data->window->draw(it->first);
	
}

void MenuState::Resume()
{
	for (auto& button : m_buttons)
        button.second = false;
    setVolume();
    m_showExtra = false;
}

void MenuState::stopMusic()
{
    if(m_data->user.getIfMusic())
        m_startMusic.play();
    else
        m_startMusic.stop();
    
}

void MenuState::setVolume()
{
    if (m_data->user.getIfSound())
        m_click.setVolume(100);
    else
        m_click.setVolume(0);

}


void MenuState::setposition()
{
    m_online.first.setPosition(800, 220);
    m_carrer.first.setPosition(1100, 220);
}

