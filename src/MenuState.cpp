#include "MenuState.h"
#include "Pictures.h"
#include "helpState.h"
#include "GetDataState.h"
#include "SettingsState.h"
#include "CareerState.h"

#include <iostream>


MenuState::MenuState(MarioKart::GameDataRef& data) :m_data(data),
                                                    m_buttons(),
                                                    m_showExtra(false)
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


    m_buttons.emplace_back(Pictures::MenuButtons1);//about
    m_buttons.back().setTextureInRect(0, 640, 255, 60);
    m_buttons.back().setInPosition(sf::Vector2f(100, 440));
    m_buttons.emplace_back(Pictures::MenuButtons1);//help
    m_buttons.back().setTextureInRect(0, 330, 187, 62);
    m_buttons.back().setInPosition(sf::Vector2f(100, 300));
    m_buttons.emplace_back(Pictures::MenuButtons1);//let spaly
    m_buttons.back().setTextureInRect(0, 250, 414, 64);
    m_buttons.back().setInPosition(sf::Vector2f(100, 200));
    m_buttons.emplace_back(Pictures::MenuButtons1);//settings
    m_buttons.back().setTextureInRect(0, 717, 360, 65);
    m_buttons.back().setInPosition(sf::Vector2f(100, 370));
    m_buttons.emplace_back(Pictures::MenuButtons1);//online
    m_buttons.back().setTextureInRect(0, 0, 265, 55);
    m_buttons.back().setInPosition(sf::Vector2f(800, 220));
    m_buttons.emplace_back(Pictures::MenuButtons1);//carrer
    m_buttons.back().setTextureInRect(0, 485, 265, 70);
    m_buttons.back().setInPosition(sf::Vector2f(1100, 220));


    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));

    m_startMusic.openFromFile(Sounds::menu);
    m_startMusic.setLoop(true);
    //m_startMusic.play();
	
    setVolume();
}

void MenuState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });

        for (auto& button : m_buttons)
        {
            if ( auto res = button.validGlobalBound(location); res)
                button.updateIfSelected(res);
        }
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
	    button.setFillInColor(255, 255, 255, 250);
	    if(button.validGlobalBound(loc))
	        button.setFillInColor(255, 255, 255, 130);
	}
}

void MenuState::Update(float dt)
{

    for( size_t i{ 0 }; i < 6; i++ )
    {
		switch (i)
		{
		case 0:
			// state about
			break;
		case 1:
			if (m_buttons[1].getIfSelected())
				m_data->stateStack.AddState(StateStack::StateRef(new helpState(m_data)), false);
			break;
		case 2:
			if (m_buttons[2].getIfSelected())
				m_showExtra = true;
			break;
		case 3:
			if (m_buttons[3].getIfSelected())
				m_data->stateStack.AddState(StateStack::StateRef(new SettingsState(m_data, m_startMusic)), false);
			break;
		case 4:
			if (m_buttons[4].getIfSelected())
			{
				m_data->user.setOnline(true);
				m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
			}
			break;
            case 5:
                if (m_buttons[5].getIfSelected())
                {
                    m_data->stateStack.AddState(StateStack::StateRef(new CareerState(m_data)), false);
                }
                break;
        }
    }
}

void MenuState::Draw()
{
	m_data->window->draw(m_background);

	for (auto it = m_buttons.begin();
		 (m_showExtra) ? it != m_buttons.cend() : it != m_buttons.cend() - 2 ; it++)
		it->draw(m_data->window);
	
}

void MenuState::Resume()
{
	for (auto& button : m_buttons)
        button.resetIfSelected();
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
