#include"helpState.h"
#include "Pictures.h"
#include "MenuState.h"

helpState::helpState(MarioKart::GameDataRef data): m_data(data), m_backMenu(false)
{
}

void helpState::Init()
{
	m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
	m_back.setTexture(Pictures::instance().getTexture(Pictures::back));

}

void helpState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseMoved) {
        auto location = m_data->window->mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });
        if (m_back.getGlobalBounds().contains(location)) {
            m_backMenu = true;
        }
    }
}

void helpState::Update(float)
{
    if (m_backMenu)
        m_data->stateStack.AddState(StateStack::StateRef(new MenuState(m_data)), true);

}

void helpState::Draw()
{
	m_data->window->draw(m_background);
	m_data->window->draw(m_back);
}

