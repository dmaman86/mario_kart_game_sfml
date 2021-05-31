#include "MenuState.h"
#include "Pictures.h"

MenuState::MenuState(MarioKart::GameDataRef data) :m_data(data)
{
}

void MenuState::Init()
{
	m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));

}

void MenuState::HandleEvent(const sf::Event& event)
{
    
        switch (event.type)
        {
        case sf::Event::Closed:
            m_data->window->close();
            break;
        }
    
}

void MenuState::Draw()
{
	m_data->window->draw(m_background);
}
