#include "GetDataState.h"
#include "Pictures.h"
#include "Fonts.h"
#include <iostream>

GetDataState::GetDataState(MarioKart::GameDataRef data): m_data( data ),
                                                         m_background(),
                                                         m_drivers(),
                                                         m_backMenu(false),
                                                         m_back()
{

}

void GetDataState::Init()
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)windowSize.x / textureSize.x,
                          (float)windowSize.y / textureSize.y);

    m_message.setFont(Fonts::instance().getFont());
    m_message.setString("Please enter your name");
    m_message.setFillColor(sf::Color::White);
    m_message.setCharacterSize(50);
    m_message.setOrigin(m_message.getLocalBounds().width / 2,
                        m_message.getLocalBounds().height / 2);
    m_message.setPosition(sf::Vector2f(windowSize.x / (unsigned)2.5,
                                       (windowSize.y / 2u) + (unsigned)100));

    m_save.setFont(Fonts::instance().getFont());
    m_save.setString("Save Data");
    m_save.setFillColor(sf::Color(76, 0, 153));
    m_save.setCharacterSize(60);
    m_save.setOrigin(m_save.getLocalBounds().width / 2,
                     m_save.getLocalBounds().height / 2);
    m_save.setPosition(sf::Vector2f(windowSize.x * 0.5f,
                                        (windowSize.y / 2) + (5 * 100)));
    m_save.setOutlineColor(sf::Color::White);
    m_save.setOutlineThickness(5.f);

    m_playerText.setFont(Fonts::instance().getFont());
    m_playerText.setCharacterSize(50);
    m_playerText.setFillColor(sf::Color::Red);
    centerOrigin(m_playerText);
    m_playerText.setPosition(sf::Vector2f(windowSize.x / 2.5, (windowSize.y / 2) + 200));

    m_back.setTexture(Pictures::instance().getTexture(Pictures::back));
    initVectorSprites(windowSize);
}

void GetDataState::initVectorSprites( const sf::Vector2u& windowSize )
{
    m_drivers.emplace_back(Pictures::MarioDriver, Pictures::instance().getTexture(Pictures::MarioDriver));
    m_drivers.emplace_back(Pictures::BowserDriver, Pictures::instance().getTexture(Pictures::BowserDriver));
    m_drivers.emplace_back(Pictures::DKDriver, Pictures::instance().getTexture(Pictures::DKDriver));
    m_drivers.emplace_back(Pictures::KoopaDriver, Pictures::instance().getTexture(Pictures::KoopaDriver));
    m_drivers.emplace_back(Pictures::LuigiDriver, Pictures::instance().getTexture(Pictures::LuigiDriver));
    m_drivers.emplace_back(Pictures::PeachDriver, Pictures::instance().getTexture(Pictures::PeachDriver));
    m_drivers.emplace_back(Pictures::ToadDriver, Pictures::instance().getTexture(Pictures::ToadDriver));
    m_drivers.emplace_back(Pictures::YoshiDriver, Pictures::instance().getTexture(Pictures::YoshiDriver));

    size_t i = 0;
    for( auto it = m_drivers.begin(); it != m_drivers.end(); it++, i+=5 )
    {
        it->second.setTextureRect(sf::Rect(99, 0, 30,30 ));
        it->second.scale(6, 6);
        it->second.setPosition( 200 + ( i * 40 ), (it->second.getGlobalBounds().height / 2) + 100);
    }
}

void GetDataState::HandleEvent(const sf::Event & event)
{
    if (event.type == sf::Event::TextEntered)
    {
        // if get text from keyboard
        if (event.text.unicode < SpecialKeyboard::MAX)
        {
            inputLogic(event.text.unicode);
        }
    }

    if(sf::Event::MouseButtonPressed == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });

        if(m_save.getGlobalBounds().contains(location))
            m_save_data = !m_save_data;
        else if (m_back.getGlobalBounds().contains(location))
            m_backMenu = !m_backMenu;
        else
        {
            for(auto& driver: m_drivers )
            {
                if(driver.second.getGlobalBounds().contains(location))
                {
                    std::cout << driver.first << std::endl;
                    driver.second.setTextureRect(sf::Rect(66, 265, 30,30 ));
                }
                else
                    driver.second.setTextureRect(sf::Rect(99, 0, 30,30 ));
            }
        }
    }
}

void GetDataState::Update(float dt)
{
    if( m_save_data )
    {
        std::cout << "Save!" << std::endl;
        std::cout << m_playerInput.toAnsiString() << std::endl;
    }
    else if (m_backMenu)
        m_data->stateStack.RemoveState();
}

void GetDataState::Draw()
{
    sf::RenderWindow& window = *m_data->window;

    window.draw(m_background);
    window.draw(m_message);
    window.draw(m_playerText);
    window.draw(m_save);
    window.draw(m_back);

    for( auto driver : m_drivers )
        window.draw( driver.second );
}

// private functions
void GetDataState::centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}

void GetDataState::inputLogic(int charTyped)
{
    if (charTyped != SpecialKeyboard::DELETE_KEY &&
        charTyped != SpecialKeyboard::ENTER_KEY &&
        charTyped != SpecialKeyboard::ESCAPE_KEY)
    {
        m_playerInput += static_cast<char>(charTyped);

        if (m_playerInput.getSize() < m_limit)
            m_playerText.setString(m_playerInput);
    }
    else if (charTyped == SpecialKeyboard::DELETE_KEY)
    {
        if (m_playerInput.getSize() > 0)
            deleteLastChar();
        m_playerText.setString(m_playerInput + "_");
    }
}

void GetDataState::deleteLastChar()
{
    sf::String tempString = "";

    for (int i = 0; i < m_playerInput.getSize() - 1; i++)
        tempString += m_playerInput[i];

    m_playerInput = tempString;
    m_playerText.setString(m_playerInput);

}

void GetDataState::saveUser()
{

}