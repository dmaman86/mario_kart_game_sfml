#include "SettingsState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "Fonts.h"


#include "SettingsState.h"
#include "Pictures.h"
#include "MenuState.h"
#include "Fonts.h"

const size_t SIZE_SHAPE = 30;
const size_t NORMAL_COLOR = 255;
const size_t TRANSPARENT_COLOR = 120;

const float POSITON_TITLE = 100;
const size_t POSITON_RECTANGLE = 500;

const int REC_TIELE2 = 717;
const int REC_TIELE3 = 360;
const int REC_TIELE4 = 65;
const unsigned WINDOW_CENTER = 2.5;

const size_t SZIE_TEXT = 50;
const unsigned POSITION_SOUND_TEXT = 100;
const unsigned POSITION_MUSIC_TEXT = 25;





SettingsState::SettingsState(MarioKart::GameDataRef& data):
    m_data(data),
    m_shapeSound(SIZE_SHAPE),
    m_shapeMusic(SIZE_SHAPE),
    StateOfMenu(data)
{
    onSound = m_data->user.getIfSound();
}

void SettingsState::Init()
{

    m_title.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons1), false);//settings
    m_title.setTextureRect(sf::Rect(0, REC_TIELE2, REC_TIELE3, REC_TIELE4));
    m_title.setPosition( float(m_windowSize.x / (unsigned)WINDOW_CENTER), POSITON_TITLE);
    m_title.setOrigin(m_title.getLocalBounds().width / 2,
        m_title.getLocalBounds().height / 2);


    m_rectangle.setTexture(Pictures::instance().getTexture(Pictures::rectangle));
    m_rectangle.setPosition(float(m_windowSize.x / (unsigned)WINDOW_CENTER), POSITON_RECTANGLE);
    m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2,
        m_rectangle.getLocalBounds().height / 2);
    m_rectangle.setColor(sf::Color(NORMAL_COLOR, NORMAL_COLOR, NORMAL_COLOR, TRANSPARENT_COLOR));
    

    //shapeSound
    if(m_data->user.getIfSound())
        m_shapeSound.setFillColor(sf::Color::Green);
    else
        m_shapeSound.setFillColor(sf::Color::Red);
    m_shapeSound.setPosition(float(m_windowSize.x / 1.6), float((m_windowSize.y / 2u) + POSITION_SOUND_TEXT));
    m_shapeSound.setOrigin(m_shapeSound.getLocalBounds().width / 2,
                           m_shapeSound.getLocalBounds().height / 2);

    //shape Meusic
    if (m_data->user.getIfMusic())
        m_shapeMusic.setFillColor(sf::Color::Green);
    else
        m_shapeMusic.setFillColor(sf::Color::Red);
    m_shapeMusic.setPosition(float(m_windowSize.x / 1.6), float((m_windowSize.y / 2u) + POSITION_MUSIC_TEXT));
    m_shapeMusic.setOrigin(m_shapeMusic.getLocalBounds().width / 2,
                           m_shapeMusic.getLocalBounds().height / 2);



    //msg Music
    m_messageMusic = createFont("Music:", sf::Color::Black, SZIE_TEXT);
    m_messageMusic.setOrigin(m_messageMusic.getLocalBounds().width / 2,
                             m_messageMusic.getLocalBounds().height / 2);
    m_messageMusic.setPosition(sf::Vector2f(float(m_windowSize.x / (unsigned)WINDOW_CENTER),
                                            float((m_windowSize.y / 2u) + POSITION_MUSIC_TEXT)));

    //msg Sound
    m_messageSound = createFont("SoundFX:", sf::Color::Black, SZIE_TEXT);
    m_messageSound.setOrigin(m_messageSound.getLocalBounds().width / 2,
                             m_messageSound.getLocalBounds().height / 2);
    m_messageSound.setPosition(sf::Vector2f(float(m_windowSize.x / (unsigned)WINDOW_CENTER),
                                            float((m_windowSize.y / 2u) + POSITION_SOUND_TEXT)));





}

void SettingsState::HandleEvent(const sf::Event& event)
{
    if (sf::Event::MouseButtonPressed == event.type) {
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });
        if(onSound)
        m_click.play();
        if (m_back->validGlobalBound(location)) {
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
    //save if sound on
    onSound = m_data->user.getIfSound();
}

void SettingsState::Draw()
{
    m_data->window->draw(m_background);
    m_data->window->draw(m_rectangle);
    m_data->window->draw(m_title);
    m_data->window->draw(m_logo);
    m_data->window->draw(*m_back.get());
    m_data->window->draw(m_shapeSound);
    m_data->window->draw(m_shapeMusic);
    m_data->window->draw(m_messageMusic);
    m_data->window->draw(m_messageSound);

}


//Puts color in a circle according to the music and sound mode
void SettingsState::setColorShape(sf::CircleShape &circle)
{
    if (circle.getFillColor() == sf::Color::Green)
    {

        if (circle.getGlobalBounds() == m_shapeSound.getGlobalBounds())
            m_data->user.setIfSound(false);
        else
        {
            m_data->menuMusic.stop();
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
            m_data->menuMusic.play();
        }

        circle.setFillColor(sf::Color::Green);
    }
}

sf::Text SettingsState::createFont(const std::string str, const sf::Color color, const int size)
{
    sf::Text text;
    text.setFont(Fonts::instance().getFont());
    text.setString(str);
    text.setFillColor(color);
    text.setCharacterSize(size);
    return text;
}