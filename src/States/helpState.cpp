#include"helpState.h"
#include "Pictures.h"
#include "MenuState.h"

helpState::helpState(MarioKart::GameDataRef& data):
    m_data(data),
    StateOfMenu(data)
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::helpStateback).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::helpStateback));
    m_background.setScale((float)windowSize.x / textureSize.x,
        (float)windowSize.y / textureSize.y);

    m_soundOn = m_data->user.getIfSound();
}

void helpState::Init()
{
   
}

void helpState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type)
    {
        if(m_soundOn)
            m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });
        if (m_back->validGlobalBound(location))
            m_data->stateStack.RemoveState();
    }
}

void helpState::Update(float)
{
}

void helpState::Draw()
{
	m_data->window->draw(m_background);
	m_data->window->draw(*m_back.get());
}


