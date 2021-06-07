#include "GetDataState.h"
#include "Pictures.h"
#include "Fonts.h"
#include "ShowUsersDataBase.h"
#include "HostState.h"
#include "Sounds.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

GetDataState::GetDataState(MarioKart::GameDataRef& data): m_data( data ),
                                                         m_background(),
                                                         m_drivers(),
                                                         m_backMenu(false),
                                                         m_back(),
                                                         m_request_post( HttpNetwork::path_user, sf::Http::Request::Post ),
                                                         m_request_put(),
                                                         m_request_del(),
                                                         m_playerText(),
                                                         m_save_data(false),
                                                         m_send_data(false),
                                                         m_effectTime(0.0f),
                                                         m_nextState(false),
                                                         m_hostPressed(false),
                                                         m_joinPressed(false)
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

    m_title_get_name.setFont(Fonts::instance().getFont());
    m_title_get_name.setString("Please enter your name");
    m_title_get_name.setFillColor(sf::Color::White);
    m_title_get_name.setCharacterSize(50);
    m_title_get_name.setOrigin(m_title_get_name.getLocalBounds().width / 2,
                               m_title_get_name.getLocalBounds().height / 2);
    m_title_get_name.setPosition(sf::Vector2f(windowSize.x / (unsigned)2.5,
                                       (windowSize.y / 2u) + (unsigned)20));

    m_hostGame.setFont(Fonts::instance().getFont());
    m_hostGame.setString("Create Game");
    m_hostGame.setFillColor(sf::Color::Green);
    m_hostGame.setCharacterSize(70);
    m_hostGame.setOrigin(m_hostGame.getLocalBounds().width / 2,
                         m_hostGame.getLocalBounds().height / 2);
    m_hostGame.setPosition(sf::Vector2f((windowSize.x / 2.5) - 100,
                                  (windowSize.y / 3) + 100));

    m_joinGame.setFont(Fonts::instance().getFont());
    m_joinGame.setString("Join to Game");
    m_joinGame.setFillColor(sf::Color::Red);
    m_joinGame.setCharacterSize(70);
    m_joinGame.setOrigin(m_joinGame.getLocalBounds().width / 2,
                         m_joinGame.getLocalBounds().height / 2);
    m_joinGame.setPosition(sf::Vector2f((windowSize.x / m_hostGame.getPosition().x) + 1200,
                                        (windowSize.y / 3 ) + 200));

    m_save.setFont(Fonts::instance().getFont());
    m_save.setString("Press Enter to Save");
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
    m_playerText.setString("_");

    m_click.setBuffer(Sounds::instance().getSoundBuffer(Sounds::click));
    setVolume();
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
        it->second.setTextureRect(sf::Rect(62, 0, 33, 30));
        it->second.scale(6, 6);
        it->second.setPosition( 150 + ( i * 40 ), (it->second.getGlobalBounds().height / 2) + 100);
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

        if (m_back.getGlobalBounds().contains(location))
        {
            m_backMenu = !m_backMenu;
        }
        else if(m_hostGame.getGlobalBounds().contains(location))
            m_hostPressed = true;
        else if(m_joinGame.getGlobalBounds().contains(location))
            m_joinPressed = true;
        else
        {
            for(auto& driver: m_drivers )
            {
                if(driver.second.getGlobalBounds().contains(location))
                {
                    m_user_sprite = driver.first;
                    driver.second.setTextureRect(sf::Rect(95, 0, 33,30 ));
                }
                else
                    driver.second.setTextureRect(sf::Rect(62, 0, 33, 30));
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
        if(m_hostPressed)
        {
            m_data->user.setHost(true);
            m_data->stateStack.AddState(StateStack::StateRef( new HostState(m_data)), false);
        }
        else if(m_joinPressed)
        {
            m_data->user.setHost(false);
            if(m_data->user.getId().size() > 0)
            {
                m_nextState = updateUser();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else
            {
                // new user
                m_data->user.setId("");
                m_nextState = saveUser();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            if(m_nextState)
                m_data->stateStack.AddState(StateStack::StateRef( new ShowUsersDataBase(m_data)), false);
        }
    }
    if (m_backMenu)
    {
        if(m_data->user.getId().size() > 0)
            deleteUser();

        m_data->stateStack.RemoveState();
    }
}

void GetDataState::Draw()
{
    sf::RenderWindow& window = *m_data->window;

    window.draw(m_background);

    if(!m_send_data)
    {
        window.draw(m_title_get_name);
        window.draw(m_playerText);
        window.draw(m_back);

        for( auto driver : m_drivers )
            window.draw( driver.second );

        if(m_save_data)
            window.draw(m_save);
    }
    else
    {
        window.draw(m_hostGame);
        window.draw(m_joinGame);
    }

}

void GetDataState::Resume()
{
    m_send_data = false;
    m_nextState = false;
    m_joinPressed = false;
    m_hostPressed = false;
    setVolume();
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

bool GetDataState::saveUser()
{
    std::ostringstream stream;
    std::stringstream ss;
    stream << "name=" << m_data->user.getName() << "&sprite=" << m_data->user.getSprite()
            << "&host=" << m_data->user.getIfHost() << "&map=" << m_data->user.getMapGame();
    m_request_post.setBody( stream.str() );
    std::cout << "line 294 " << stream.str() << std::endl;

    sf::Http::Response response = m_data->http.sendRequest( m_request_post );

    if( response.getStatus() != sf::Http::Response::Created )
    {
        std::cout << "line 299 " << response.getBody() << std::endl;
        return false;
    }
    ss << response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);
    m_data->user.setId( pt.get<std::string>("id") );
    return true;
}

bool GetDataState::updateUser()
{
    m_request_put.setMethod( sf::Http::Request::Put );
    m_request_put.setUri( HttpNetwork::path_user + "/" + m_data->user.getId() );
    std::ostringstream stream;
    stream << "name=" << m_data->user.getName() << "&sprite=" << m_data->user.getSprite();
    stream << "&host=" << m_data->user.getIfHost() << "&map=" << m_data->user.getMapGame();
    m_request_put.setField("Content-Type", "application/x-www-form-urlencoded");
    m_request_put.setBody(stream.str());

    sf::Http::Response response = m_data->http.sendRequest( m_request_put );

    if( response.getStatus() != sf::Http::Response::Ok )
    {
        std::cout << "line 299 " << response.getBody() << std::endl;
        return false;
    }
    return true;
}

bool GetDataState::deleteUser()
{
    m_request_del.setMethod(sf::Http::Request::Delete);
    m_request_del.setUri(HttpNetwork::path_user + "/" + m_data->user.getId() );

    sf::Http::Response response = m_data->http.sendRequest( m_request_del );

    if( response.getStatus() != sf::Http::Response::Ok )
        return false;
    return true;
}

void GetDataState::setVolume()
{
    if (m_data->user.getIfSound())
        m_click.setVolume(100);
    else
        m_click.setVolume(0);

}