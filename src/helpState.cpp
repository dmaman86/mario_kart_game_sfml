#include"helpState.h"
#include "Pictures.h"
#include "MenuState.h"

helpState::helpState(MarioKart::GameDataRef data): m_data(data),
                                                    m_backMenu(false),
                                                    m_background()
{
}

void helpState::Init()
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)windowSize.x / textureSize.x,
                          (float)windowSize.y / textureSize.y);

    m_back.setTexture(Pictures::instance().getTexture(Pictures::back));
    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));
}

void helpState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });
        if (m_back.getGlobalBounds().contains(location)) {
            m_backMenu = true;
        }
    }
}

void helpState::Update(float)
{
    setVolume();
    if (m_backMenu)
    {
        m_data->stateStack.RemoveState();
    }
}

void helpState::Draw()
{
	m_data->window->draw(m_background);
	m_data->window->draw(m_back);
}

void helpState::setVolume()
{
    if(m_data->user.getIfSound())
        m_click.setVolume(100);
    else
        m_click.setVolume(0);
}

