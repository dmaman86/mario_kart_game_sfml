#include "WelcomeState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "Fonts.h"

WelcomeState::WelcomeState(MarioKart::GameDataRef data) :
    m_data(data),
    m_nextState(false),
    m_showText(true),
    mTextEffectTime(0.0f),
    m_background()
{
}

//init all the object
//=============================================================
void WelcomeState::Init()
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    //the the background
	m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)windowSize.x / textureSize.x,
                               (float)windowSize.y / textureSize.y);


    //set the text
    m_text = sf::Text("Press enter to continue", Fonts::instance().getFont(), 35);
    m_text.setFillColor(sf::Color(76, 0, 153));
    m_text.setOrigin(m_text.getLocalBounds().width / 2,
                     m_text.getLocalBounds().height / 2);
    m_text.setPosition(sf::Vector2f(float(windowSize.x) * 0.5f,
                                   (float(windowSize.y / 2.f)) + 300.f));
    m_text.setOutlineColor(sf::Color::White);
    m_text.setOutlineThickness(5.f);


    //set the logo
    m_logoMario.setTexture(Pictures::instance().getTexture(Pictures::marioLogo));
    m_logoMario.setOrigin(m_logoMario.getGlobalBounds().width / 2,
                          m_logoMario.getGlobalBounds().height / 2);
    m_logoMario.setPosition(sf::Vector2f(float(windowSize.x /2), float(windowSize.y /2) - 100.f) );
}

//take handle event
//=============================================================
void WelcomeState::HandleEvent(const sf::Event&)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        m_nextState = true;
}

//=============================================================
void WelcomeState::Update(float dt)
{
    if(m_nextState)
        m_data->stateStack.AddState(StateStack::StateRef(new MenuState(m_data)));

    //Displays the TEXT flashing
    mTextEffectTime += dt;
    if(mTextEffectTime >= 0.5f)
    {
        m_showText = !m_showText;
        mTextEffectTime = 0.0f;
    }

}
//draw 
//=============================================================
void WelcomeState::Draw()
{
    sf::RenderWindow& window = *m_data->window;
    
	window.draw(m_background);
    window.draw(m_logoMario);

    if(m_showText)
        window.draw(m_text);

}
