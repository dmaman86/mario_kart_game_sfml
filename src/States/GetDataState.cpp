#include "GetDataState.h"
#include "Pictures.h"
#include "Fonts.h"
#include "ShowUsersDataBase.h"
#include "HostState.h"
#include "Sounds.h"
#include <thread>
#include <chrono>
#include "RaceStatesBase.h"
#include "HostState.h"
#include "CareerMenu.h"

GetDataState::GetDataState(MarioKart::GameDataRef& data): m_data( data ),
                                                         m_background(),
                                                         m_drivers(),
                                                         m_back(Pictures::MenuButtons1),
                                                         m_playerText(),
                                                         m_save_data(false),
                                                         m_send_data(false),
                                                         m_effectTime(0.0f),
                                                         m_nextState(false),
                                                         m_save(Pictures::MenuButtons1),
                                                         m_joinGame(Pictures::MenuButtons1),
                                                         m_createGame(Pictures::MenuButtons1),
                                                         m_errorShow(false)
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

    initTexts(windowSize);

    m_save.setTextureInRect(PositionButtons::save);
    m_save.setInOrigin();
    m_save.setInPosition(sf::Vector2f(windowSize.x * 0.5f,
                                      (windowSize.y / 2) + 300));

    m_createGame.setTextureInRect(PositionButtons::createGame);
    m_createGame.setInOrigin();
    m_createGame.setInPosition(sf::Vector2f((windowSize.x / 2.5) - 100,
                                            (windowSize.y / 3) + 100));
    m_createGame.setCallback([this](){
        m_data->user.setHost(true);
        m_data->stateStack.AddState(StateStack::StateRef( new HostState(m_data)), false);
    });

    m_joinGame.setTextureInRect(PositionButtons::joinGame);
    m_joinGame.setInOrigin();
    m_joinGame.setInPosition(sf::Vector2f((windowSize.x / m_createGame.getInPosition().x) + 1000,
                                          (windowSize.y / 3 ) + 200));
    m_joinGame.setCallback([this](){
        m_data->stateStack.AddState(StateStack::StateRef( new ShowUsersDataBase(m_data)), false);
    });

    m_playerText.setFont(Fonts::instance().getFont());
    m_playerText.setCharacterSize(50);
    m_playerText.setFillColor(sf::Color::Red);
    centerOrigin(m_playerText);
    m_playerText.setPosition(sf::Vector2f(windowSize.x / 2.5, (windowSize.y / 2) + 200));

    m_back.setCallback([this](){
        m_data->user.setOnline(false);
        m_data->stateStack.RemoveState();
    });
    if(m_data->user.getOnline())
        initVectorSpritesOnline(windowSize);
    else
        initVectorSpritesOffline(windowSize);

    m_playerText.setString("_");

    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));
    setVolume();
    m_back.setTextureInRect(PositionButtons::back);
}

void GetDataState::initVectorSpritesOnline( const sf::Vector2u& windowSize )
{
    m_drivers.emplace_back(std::make_shared<Button>(Pictures::MarioDriver));
    m_drivers.emplace_back(std::make_shared<Button>(Pictures::BowserDriver));
    m_drivers.emplace_back(std::make_shared<Button>(Pictures::DKDriver));
    m_drivers.emplace_back(std::make_shared<Button>(Pictures::KoopaDriver));
    m_drivers.emplace_back(std::make_shared<Button>(Pictures::LuigiDriver));
    m_drivers.emplace_back(std::make_shared<Button>(Pictures::PeachDriver));
    m_drivers.emplace_back(std::make_shared<Button>(Pictures::ToadDriver));
    m_drivers.emplace_back(std::make_shared<Button>(Pictures::YoshiDriver));

    size_t i = 0;
    for( auto it = m_drivers.begin(); it != m_drivers.end(); it++, i+=5 )
    {
        it->get()->setTextureInRect(PositionDrive::start);
        it->get()->setInScale(5, 5);
        it->get()->setInPosition(sf::Vector2f(120 + ( i * 30 ), (windowSize.y / 2 ) - 200));
    }
}

void GetDataState::initVectorSpritesOffline(const sf::Vector2u & windowSize)
{
    size_t j = 0;
    for(size_t i{0}; i < m_data->user.getMaxDrivers(); i++, j += 5)
    {
        auto button = std::make_shared<Button>(m_data->user.getDrive(i));
        button->setTextureInRect(PositionDrive::start);
        button->setIntoScale(5, 5);
        button->setInPosition(sf::Vector2f(120 + ( j * 30 ), (windowSize.y / 2 ) - 200));
        m_drivers.emplace_back(button);
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
        m_click.play();
        auto location = m_data->window->mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });

        if (auto res = m_back.validGlobalBound(location); res)
            m_back.updateIfSelected(res);

        else if(auto res = m_createGame.validGlobalBound(location); res)
            m_createGame.updateIfSelected(res);
        else if(auto res = m_joinGame.validGlobalBound(location); res)
            m_joinGame.updateIfSelected(res);
        else
        {
            for(size_t i{0}; i < m_drivers.size(); i++)
            {
                auto& driver = m_drivers[i];
                if(auto res = driver->validGlobalBound(location); res)
                {
                    driver->updateIfSelected(res);
                    m_user_sprite = driver->getName();
                    driver->setTextureInRect(PositionDrive::select);
                    resetOtherDrivers(i);
                }
            }
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_click.play();
        if(m_save_data)
        {
            std::string name = std::string(m_playerInput.toAnsiString());
            name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
            std::string sprite = m_user_sprite;
            sprite.erase(std::remove(sprite.begin(), sprite.end(), '\n'), sprite.end());
            m_data->user.setName(name );
            m_data->user.setSprite(sprite);
            m_send_data = true;
        }
    }
}

void GetDataState::resetOtherDrivers(size_t index)
{
    for(size_t i{0}; i < m_drivers.size(); i++)
    {
        if( i != index)
            m_drivers[i]->setTextureInRect(PositionDrive::start);
    }
}

void GetDataState::Update(float dt)
{
    if(!m_playerInput.toAnsiString().empty() && !m_user_sprite.empty())
        m_save_data = true;

    if(m_save_data)
    {
        m_effectTime += (float)dt;
        if(m_effectTime >= 0.5f)
        {
            m_save_data = !m_save_data;
            m_effectTime = 0.0f;
        }
    }
    if( m_send_data )
    {
        if(m_data->user.getOnline())
        {
            if(m_createGame.getIfSelected())
                m_createGame.initCallback();
            else if(m_joinGame.getIfSelected())
            {
                m_data->user.setHost(false);
                m_nextState = (m_data->user.getId().size() < 1 ) ?
                                m_data->services.createUser(&m_data->user) :
                                m_data->services.updateUser(&m_data->user);

                if(!m_nextState)
                    m_errorShow = true;
                else
                    m_joinGame.initCallback();
            }
        }
        else
            m_data->stateStack.AddState(StateStack::StateRef(new CareerMenu(m_data)), false);
    }
    if (m_back.getIfSelected())
    {
        if(m_data->user.getId().size() > 0)
            m_data->services.deleteUser(&m_data->user);
        m_back.initCallback();
    }
}

void GetDataState::Draw()
{
    sf::RenderWindow& window = *m_data->window;

    window.draw(m_background);
    window.draw(m_back);
    if(!m_errorShow)
    {
        if(!m_send_data)
        {
            window.draw(m_title_get_name);
            window.draw(m_playerText);

            for( auto driver : m_drivers )
                window.draw(*driver.get());

            if(m_save_data)
                window.draw(m_save);
        }
        else if( m_send_data && m_data->user.getOnline())
        {
            window.draw(m_createGame);
            window.draw(m_joinGame);
        }
    }
    else
    {
        window.draw(m_back);
        window.draw(m_error);
    }

}

void GetDataState::Resume()
{
    m_send_data = false;
    m_nextState = false;
    m_save_data = false;
    m_save.resetIfSelected();
    m_joinGame.resetIfSelected();
    m_createGame.resetIfSelected();
    m_back.resetIfSelected();
    setVolume();
    if(m_data->user.getId().size() > 1)
        m_data->services.deleteUser(&m_data->user);
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

void GetDataState::setVolume()
{
    if (m_data->user.getIfSound())
        m_click.setVolume(100);
    else
        m_click.setVolume(0);

}

void GetDataState::initTexts(const sf::Vector2u& windowSize)
{
    m_title_get_name.setFont(Fonts::instance().getFont());
    m_title_get_name.setString("Please enter your name");
    m_title_get_name.setFillColor(sf::Color::White);
    m_title_get_name.setCharacterSize(50);
    m_title_get_name.setOrigin(m_title_get_name.getLocalBounds().width / 2,
                               m_title_get_name.getLocalBounds().height / 2);
    m_title_get_name.setPosition(sf::Vector2f(windowSize.x / (unsigned)2.5,
                                              (windowSize.y / 2u) + (unsigned)20));

    m_error.setFont(Fonts::instance().getFont());
    m_error.setString("Error to connect with serve");
    m_error.setFillColor(sf::Color::Red);
    m_error.setCharacterSize(50);
    m_error.setOrigin(m_error.getLocalBounds().width / 2,
                      m_error.getLocalBounds().height / 2);
    m_error.setPosition(sf::Vector2f(windowSize.x / 2,
                                     windowSize.y / 2));
}