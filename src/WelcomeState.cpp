#include "WelcomeState.h"
#include "Pictures.h"
#include "MenuState.h"
WelcomeState::WelcomeState(MarioKart::GameDataRef data) :m_data(data), m_nextState(false)
{
}

void WelcomeState::Init()
{
	m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_logoMario.setTexture(Pictures::instance().getTexture(Pictures::marioLogo));
    setposition();

}

void WelcomeState::HandleEvent(const sf::Event& event)
{
    
        switch (event.type)
        {
        case sf::Event::Closed:
            m_data->window->close();
            break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            m_nextState = true;
    
}

void WelcomeState::Update(float)
{
    if(m_nextState)
        m_data->stateStack.AddState(StateStack::StateRef(new MenuState(m_data)), false);

}

void WelcomeState::Draw()
{
	m_data->window->draw(m_background);
    m_data->window->draw(m_logoMario);
    m_data->window->draw(m_logoSuper);

}

void WelcomeState::setposition()
{
    m_logoMario.setPosition(450,200);
}
