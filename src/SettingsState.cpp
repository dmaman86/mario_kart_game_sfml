#include "SettingsState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "Fonts.h"

SettingsState::SettingsState(MarioKart::GameDataRef& data): m_data(data), m_shapeSound(30), m_shapeMusic(30)
{
    InitOfMenu(m_data);
}

void SettingsState::Init()
{

    //title
    m_title.setTexture(Pictures::instance().getTexture(Pictures::settings));
    m_title.setPosition(m_windowSize.x / (unsigned)2.5 , 100);
    m_title.setOrigin(m_title.getLocalBounds().width / 2,
                      m_title.getLocalBounds().height / 2);

    //shapeSound
    if(m_data->user.getIfSound())
        m_shapeSound.setFillColor(sf::Color::Green);
    else
        m_shapeSound.setFillColor(sf::Color::Red);
    m_shapeSound.setPosition(m_windowSize.x / 1.7, ((m_windowSize.y / 2u) - 185));
    m_shapeSound.setOrigin(m_shapeSound.getLocalBounds().width / 2,
                           m_shapeSound.getLocalBounds().height / 2);

    //shape Meusic
    m_shapeMusic.setFillColor(sf::Color::Green);
    m_shapeMusic.setPosition(m_windowSize.x / 1.7, ((m_windowSize.y / 2u) - 75));
    m_shapeMusic.setOrigin(m_shapeMusic.getLocalBounds().width / 2,
                           m_shapeMusic.getLocalBounds().height / 2);



    //msg Music
    m_messageMusic = createFont("Music:", sf::Color::Black, 50);
    m_messageMusic.setOrigin(m_messageMusic.getLocalBounds().width / 2,
                             m_messageMusic.getLocalBounds().height / 2);
    m_messageMusic.setPosition(sf::Vector2f(m_windowSize.x / (unsigned)2.5,
                                            (m_windowSize.y / 2u) + -100));

    //msg Sound
    m_messageSound = createFont("SoundFX:", sf::Color::Black, 50);
    m_messageSound.setOrigin(m_messageSound.getLocalBounds().width / 2,
                             m_messageSound.getLocalBounds().height / 2);
    m_messageSound.setPosition(sf::Vector2f(m_windowSize.x / (unsigned)2.5,
                                            (m_windowSize.y / 2u) - 200));


}

void SettingsState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });
        m_click.play();

        if (m_back.getGlobalBounds().contains(location)) {
            m_backMenu = true;
        }
        else if (m_shapeSound.getGlobalBounds().contains(location))
        {
            if (m_shapeSound.getFillColor() == sf::Color::Green)
            {
                m_data->user.setIfSound(false);
                m_shapeSound.setFillColor(sf::Color::Red);
            }
            else
            {
                m_data->user.setIfSound(true);
                m_shapeSound.setFillColor(sf::Color::Green);
            }

        }
        else if (m_shapeMusic.getGlobalBounds().contains(location))
        {
            m_shapeMusic.setFillColor(sf::Color::Red);

        }
    }
}

void SettingsState::Update(float)
{
    setVolume(m_data->user.getIfSound());

    if (m_backMenu)
    {
        m_data->stateStack.RemoveState();
    }
}

void SettingsState::Draw()
{
    m_data->window->draw(m_background);
    m_data->window->draw(m_title);
    m_data->window->draw(m_back);
    m_data->window->draw(m_shapeSound);
    m_data->window->draw(m_shapeMusic);
    m_data->window->draw(m_messageMusic);
    m_data->window->draw(m_messageSound);

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