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
          m_validConnection(true),
          m_request_get( HttpNetwork::path, sf::Http::Request::Get ),
          m_request_post( HttpNetwork::path, sf::Http::Request::Post ),
          m_user("", "david", "mario_kart.png")
{

}

void TestState::Init()
{
    sf::Vector2u textureSize, windowSize;
    sf::Texture backTexture = Pictures::instance().getTexture(Pictures::menuBackground);
    windowSize = m_data->window->getSize();
    textureSize = backTexture.getSize();

    m_BackgroundSprite.setTexture(backTexture);
    m_BackgroundSprite.setScale((float)windowSize.x / textureSize.x,
                                (float)windowSize.y / textureSize.y);

    saveUser();
    getUsers();
    buildList(windowSize);
}

void TestState::buildList( const sf::Vector2u& windowSize )
{
    size_t i = 0;
    for( auto itr = m_users.begin(); itr != m_users.end(); i++, itr++ )
    {
        sf::Text text;
        text.setFont(Fonts::instance().getFont());
        text.setCharacterSize(70);
        text.setStyle(sf::Text::Bold);
        text.setString( (*itr).getName() );
        m_list.push_back(text);
        m_list[i].setFillColor(sf::Color::White);

        m_list[i].setOrigin(m_list[i].getLocalBounds().width / 2,
                               m_list[i].getLocalBounds().height / 2);
        m_list[i].setPosition(sf::Vector2f(windowSize.x / 2.5,
                                              (windowSize.y / 2u) + (i * 100)));
        m_list[i].setOutlineColor(sf::Color(76, 0, 153));
        m_list[i].setOutlineThickness(5.f);
    }
}

void TestState::getUsers()
{
    std::stringstream stream;
    sf::Http::Response response = m_data->http.sendRequest(m_request_get);

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

void TestState::saveUser()
{
    std::ostringstream stream;
    std::stringstream ss;
    stream << "name=" << m_user.getName() << "&sprite=" << m_user.getSprite();
    m_request_post.setBody( stream.str() );

    sf::Http::Response response = m_data->http.sendRequest( m_request_post );

    if( response.getStatus() != sf::Http::Response::Created )
        m_validConnection = false;
    else
    {
        ss << response.getBody();
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        m_user.setId( pt.get<std::string>("id") );
    }

}

void TestState::buildVecUsers(boost::property_tree::ptree const& pt)
{
    using boost::property_tree::ptree;
    std::vector< std::string > values;
    for (ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        values.emplace_back( it->second.get_value<std::string>() );
    }
    if( values[0] != m_user.getId() )
    {
        UserNetwork user( values[ 0 ], values[ 1 ], values[ 2 ] );
        m_users.emplace_back( user );
    }
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

    for( auto item : m_list )
        window.draw(item);

}

void TestState::centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}
