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

    auto buttonAbout = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonAbout->setTextureInRect(0, 640, 255, 60);
    buttonAbout->setInPosition(sf::Vector2f(100, 440));
    auto buttonHelp = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonHelp->setTextureInRect(0, 330, 187, 62);
    buttonHelp->setInPosition(sf::Vector2f(100, 300));
    buttonHelp->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new helpState(m_data)), false);
    });
    auto buttonLetPlay = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonLetPlay->setTextureInRect(0, 250, 414, 64);
    buttonLetPlay->setInPosition(sf::Vector2f(100, 200));
    auto buttonSettings = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonSettings->setTextureInRect(0, 717, 360, 65);
    buttonSettings->setInPosition(sf::Vector2f(100, 370));
    buttonSettings->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new SettingsState(m_data, m_startMusic)), false);
    });
    m_button_online = std::make_shared<Button>(Pictures::MenuButtons1);
    m_button_online->setTextureInRect(0, 0, 265, 55);
    m_button_online->setInPosition(sf::Vector2f(800, 220));
    m_button_online->setCallback([this](){
        m_data->user.setOnline(true);
        m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
    });
    m_button_carer = std::make_shared<Button>(Pictures::MenuButtons1);
    m_button_carer->setTextureInRect(0, 485, 265, 70);
    m_button_carer->setInPosition(sf::Vector2f(1100, 220));
    m_button_carer->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new CareerState(m_data)), false);
    });

    m_buttons[Options::Help] = buttonHelp;
    m_buttons[Options::About] = buttonAbout;
    m_buttons[Options::Settings] = buttonSettings;
    m_buttons[Options::LetPlay] = buttonLetPlay;


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

        if(m_showExtra)
        {
            if(auto res = m_button_online->validGlobalBound(location); res)
                m_button_online->updateIfSelected(res);
            if(auto res = m_button_carer->validGlobalBound(location); res)
                m_button_carer->updateIfSelected(res);
        }

        for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
        {
            if(auto res = it->second->validGlobalBound(location); res)
                it->second->updateIfSelected(res);
        }
    }
    if (sf::Event::MouseMoved == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseMove.x, event.mouseMove.y });

		updateColors(location);
    }
}

void MenuState::updateColors(const sf::Vector2f& loc)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        it->second->setFillInColor(255, 255, 255, 250);
        if(it->second->validGlobalBound(loc))
            it->second->setFillInColor(255, 255, 255, 130);
    }
}

void MenuState::Update(float dt)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
		switch (it->first)
		{
		    case Options::About:
			    // state about
			    break;
		    case Options::Help:
			    if (it->second->getIfSelected())
                    it->second->initCallback();
			    break;
		    case Options::LetPlay:
			    if (it->second->getIfSelected())
				    m_showExtra = true;
			    break;
		    case Options::Settings:
			    if (it->second->getIfSelected())
                    it->second->initCallback();
			    break;
        }
    }
    if(m_button_online->getIfSelected())
        m_button_online->initCallback();
    if(m_button_carer->getIfSelected())
        m_button_carer->initCallback();
}

void MenuState::Draw()
{
	m_data->window->draw(m_background);

	for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
        m_data->window->draw(*it->second.get());

	if(m_showExtra)
    {
	    m_data->window->draw(*m_button_online.get());
	    m_data->window->draw(*m_button_carer.get());
    }
}

void MenuState::Resume()
{
	for (auto& button : m_buttons)
        button.second->resetIfSelected();
	m_button_carer->resetIfSelected();
	m_button_online->resetIfSelected();
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
