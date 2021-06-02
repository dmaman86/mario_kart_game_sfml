#include "TestState.h"
#include "Fonts.h"
#include "Pictures.h"
#include <sstream>
#include <iostream>

TestState::TestState(MarioKart::GameDataRef data)
        : m_data( data ),
          m_users(),
          m_BackgroundSprite(),
          m_title(),
          m_validConnection(true)
{

}

void TestState::Init()
{
    sf::Vector2u textureSize, windowSize;
    sf::Texture backTexture = Pictures::instance().getTexture(Pictures::menuBackground);
    windowSize = m_data->window->getSize();
    textureSize = backTexture.getSize();

    m_BackgroundSprite.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_BackgroundSprite.setScale((float)windowSize.x / textureSize.x,
                                (float)windowSize.y / textureSize.y);
    std::stringstream stream;

    sf::Http::Request request(HttpNetwork::get_users, sf::Http::Request::Get );

    sf::Http::Response response = m_data->http.sendRequest(request);

    if( response.getStatus() == sf::Http::Response::Ok )
    {
        stream << response.getBody();
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(stream, pt);

        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("users"))
                    {
                        assert(v.first.empty()); // array elements have no names
                        buildVecUsers(v.second);
                    }
    }
    else
        m_validConnection = false;
}

void TestState::buildVecUsers(boost::property_tree::ptree const& pt)
{
    using boost::property_tree::ptree;
    std::vector< std::string > values;
    for (ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        values.emplace_back( it->second.get_value<std::string>() );
    }
    UserNetwork user( values[ 0 ], values[ 1 ], values[ 2 ], values[ 3 ] );
    m_users.emplace_back( user );
}

void TestState::HandleEvent(const sf::Event & event)
{
    if (sf::Event::Closed == event.type)
    {
        m_data->window->close();
    }
}

void TestState::Update(float dt)
{
    if(!m_validConnection)
        m_data->stateStack.RemoveState();
}

void TestState::Draw()
{
    sf::RenderWindow& window = *m_data->window;
    window.draw(m_BackgroundSprite);
    int i = 1;
    for( auto& user : m_users )
    {
        sf::Text m_userName( user.getName(), Fonts::instance().getFont(), 30);
        sf::Text m_userLevel( user.getLevel(), Fonts::instance().getFont(), 30);
        sf::Text m_userSprite( user.getSprite(), Fonts::instance().getFont(), 30 );

        m_userName.setPosition(sf::Vector2f(window.getSize().x / 2.5 - 250,
                                            (window.getSize().y / 2) + (i * 100) - 200 ));

        m_userLevel.setPosition(sf::Vector2f(window.getSize().x / 2.5 + 600,
                                             (window.getSize().y / 2) + (i * 100) - 200 ));

        m_userSprite.setPosition(sf::Vector2f(window.getSize().x / 2.5 + 600,
                                              (window.getSize().y / 2) + (i * 100) - 200 ));

        window.draw(m_userName);
        window.draw(m_userLevel);
        i++;
    }
    i = 1;
}

void TestState::centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}
