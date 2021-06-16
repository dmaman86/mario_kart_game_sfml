#include"helpState.h"
#include "Pictures.h"
#include "MenuState.h"

helpState::helpState(MarioKart::GameDataRef& data): m_data(data)
{
    InitOfMenu(m_data);
}

void helpState::Init()
{
}

void helpState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });
        if (m_back.getGlobalBounds().contains(location)) {
            m_data->stateStack.RemoveState();

        }
    }
}

void helpState::Update(float)
{
    setVolume(m_data->user.getIfSound());
}

void helpState::Draw()
{
	m_data->window->draw(m_background);
	m_data->window->draw(m_back);
}


