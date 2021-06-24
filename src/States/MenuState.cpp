#include "MenuState.h"
#include "Pictures.h"
#include "helpState.h"
#include "GetDataState.h"
#include "SettingsState.h"
#include "CareerState.h"
#include <iostream>


MenuState::MenuState(MarioKart::GameDataRef& data) :m_data(data),
                                                    m_buttons(),
                                                    m_showExtra(false),
                                                    m_rect_logo()
{
    setVolume();
}

void MenuState::Init()
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)windowSize.x / textureSize.x,
                          (float)windowSize.y / textureSize.y);

    auto sprite = sf::Sprite();
    sprite.setTexture(Pictures::instance().getTexture(Pictures::marioLogo));
    m_rect_logo.setTexture(sprite.getTexture());
    m_rect_logo.setSize(sf::Vector2f(450, 250));
    m_rect_logo.setOrigin(m_rect_logo.getGlobalBounds().width / 2,
                          m_rect_logo.getGlobalBounds().height / 2);
    m_rect_logo.setPosition(sf::Vector2f(float(windowSize.x /2), float((windowSize.y /2) - 250)) );


    auto buttonLetPlay = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonLetPlay->setTextureInRect(PositionButtons::letPlay);
    buttonLetPlay->setInPosition(sf::Vector2f(100, 350));

    auto buttonSettings = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonSettings->setTextureInRect(PositionButtons::settings);
    buttonSettings->setInPosition(sf::Vector2f(100, 450));
    buttonSettings->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new SettingsState(m_data)), false);
    });

    auto buttonHelp = std::make_shared<Button>(Pictures::MenuButtons1);
    buttonHelp->setTextureInRect(PositionButtons::help);
    buttonHelp->setInPosition(sf::Vector2f(100, 540));
    buttonHelp->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new helpState(m_data)), false);
    });
    m_button_online = std::make_shared<Button>(Pictures::MenuButtons1);
    m_button_online->setTextureInRect(PositionButtons::online);
    m_button_online->setInPosition(sf::Vector2f(800, 350));
    m_button_online->setCallback([this](){
        m_data->user.setOnline(true);
        m_data->stateStack.AddState(StateStack::StateRef(new GetDataState(m_data)), false);
    });
    m_button_carer = std::make_shared<Button>(Pictures::MenuButtons1);
    m_button_carer->setTextureInRect(PositionButtons::carer);
    m_button_carer->setInPosition(sf::Vector2f(1100, 350));
    m_button_carer->setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef(new CareerState(m_data)), false);
    });

    m_buttons[Options::Help] = buttonHelp;
    m_buttons[Options::Settings] = buttonSettings;
    m_buttons[Options::LetPlay] = buttonLetPlay;

    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));

    stopMusic();
}

void MenuState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
        if(m_onSound)
            m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });

        if(m_showExtra)
        {
            if(m_button_online->validGlobalBound(location))
                m_button_online->initCallback();
            if(m_button_carer->validGlobalBound(location))
                m_button_carer->initCallback();
        }

        for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
        {
            if(it->second->validGlobalBound(location))
            {
                if(it->first == Options::LetPlay)
                    m_showExtra = true;
                else
                    it->second->initCallback();
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

void MenuState::updateColors(const sf::Vector2f& loc)
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); it++)
    {
        it->second->setFillInColor(255, 255, 255, 250);
        if(it->second->validGlobalBound(loc))
            it->second->setFillInColor(255, 255, 255, 130);
    }

    m_button_carer->setFillInColor(255, 255, 255, 250);
    m_button_online->setFillInColor(255, 255, 255, 250);

    if (m_button_online->validGlobalBound(loc))
    {
        m_button_online->setFillInColor(255, 255, 255, 130);
    }
    else if(m_button_carer->validGlobalBound(loc))
    {
        m_button_carer->setFillInColor(255, 255, 255, 130);
    }
}

void MenuState::Update(const float)
{
    setVolume();
}

void MenuState::Draw()
{
	m_data->window->draw(m_background);
	m_data->window->draw(m_rect_logo);

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
    setVolume();
    m_showExtra = false;
}

void MenuState::stopMusic()
{
    if(m_data->user.getIfMusic())
        m_data->menuMusic.play();
    else
        m_data->menuMusic.stop();
    
}

void MenuState::setVolume()
{
    m_onSound = m_data->user.getIfSound();
}
