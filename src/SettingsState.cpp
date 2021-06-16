#include "SettingsState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "Fonts.h"

SettingsState::SettingsState(MarioKart::GameDataRef& data, sf::Music& menuMusic): m_data(data), m_shapeSound(30), m_shapeMusic(30), m_menuMusic(menuMusic)
{
      
    InitOfMenu(m_data);
}

void SettingsState::Init()
{

    

    m_title.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//settings
    m_title.setTextureRect(sf::Rect(0, 717, 360, 65));
    m_title.setPosition(m_windowSize.x / (unsigned)2.5, 100);
    m_title.setOrigin(m_title.getLocalBounds().width / 2,
        m_title.getLocalBounds().height / 2);





    m_rectangle.setTexture(Pictures::instance().getTexture(Pictures::rectangle));
    m_rectangle.setPosition(m_windowSize.x / (unsigned)2.5, 500);
    m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2,
        m_rectangle.getLocalBounds().height / 2);
    m_rectangle.setColor(sf::Color(255, 255, 255, 120));
    

    //shapeSound
    if(m_data->user.getIfSound())
        m_shapeSound.setFillColor(sf::Color::Green);
    else
        m_shapeSound.setFillColor(sf::Color::Red);
    m_shapeSound.setPosition(m_windowSize.x / 1.6, ((m_windowSize.y / 2u) + 100));
    m_shapeSound.setOrigin(m_shapeSound.getLocalBounds().width / 2,
                           m_shapeSound.getLocalBounds().height / 2);

    //shape Meusic
    if (m_data->user.getIfMusic())
        m_shapeMusic.setFillColor(sf::Color::Green);
    else
        m_shapeMusic.setFillColor(sf::Color::Red);
    m_shapeMusic.setPosition(m_windowSize.x / 1.6, ((m_windowSize.y / 2u) + 25));
    m_shapeMusic.setOrigin(m_shapeMusic.getLocalBounds().width / 2,
                           m_shapeMusic.getLocalBounds().height / 2);



    //msg Music
    m_messageMusic = createFont("Music:", sf::Color::Black, 50);
    m_messageMusic.setOrigin(m_messageMusic.getLocalBounds().width / 2,
                             m_messageMusic.getLocalBounds().height / 2);
    m_messageMusic.setPosition(sf::Vector2f(m_windowSize.x / (unsigned)2.5,
                                            (m_windowSize.y / 2u) + 25));

    //msg Sound
    m_messageSound = createFont("SoundFX:", sf::Color::Black, 50);
    m_messageSound.setOrigin(m_messageSound.getLocalBounds().width / 2,
                             m_messageSound.getLocalBounds().height / 2);
    m_messageSound.setPosition(sf::Vector2f(m_windowSize.x / (unsigned)2.5,
                                            (m_windowSize.y / 2u) + 100));





}

void SettingsState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });
        m_click.play();
        if (m_back.getGlobalBounds().contains(location)) {
            m_data->stateStack.RemoveState();
        }
        else if (m_shapeSound.getGlobalBounds().contains(location))
        {
            setColorShape(m_shapeSound);
        }
        else if (m_shapeMusic.getGlobalBounds().contains(location))
        {
            setColorShape(m_shapeMusic);
        }
    }
}

void SettingsState::Update(float)
{
    setVolume(m_data->user.getIfSound());
}

void SettingsState::Draw()
{
    m_data->window->draw(m_background);
    m_data->window->draw(m_rectangle);
    m_data->window->draw(m_title);
    m_data->window->draw(m_back);
    m_data->window->draw(m_shapeSound);
    m_data->window->draw(m_shapeMusic);
    m_data->window->draw(m_messageMusic);
    m_data->window->draw(m_messageSound);

}

void SettingsState::setColorShape(sf::CircleShape &circle)
{
    if (circle.getFillColor() == sf::Color::Green)
    {

        if (circle.getGlobalBounds() == m_shapeSound.getGlobalBounds())
            m_data->user.setIfSound(false);
        else
        {
            m_menuMusic.stop();
            m_data->user.setIfMusic(false);
        }

        circle.setFillColor(sf::Color::Red);
    }
    else
    {
        if (circle.getGlobalBounds() == m_shapeSound.getGlobalBounds())
            m_data->user.setIfSound(true);
        else
        {
            m_data->user.setIfMusic(true);
            m_menuMusic.play();
        }

        circle.setFillColor(sf::Color::Green);
    }
}

sf::Text SettingsState::createFont(std::string str, sf::Color color, int size)
{
    sf::Text text;
    text.setFont(Fonts::instance().getFont());
    text.setString(str);
    text.setFillColor(color);
    text.setCharacterSize(size);
    return text;
}