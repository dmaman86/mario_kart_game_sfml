#include "ShowUsersDataBase.h"
#include "Pictures.h"
#include "Fonts.h"
#include <iostream>

ShowUsersDataBase::ShowUsersDataBase(MarioKart::GameDataRef data, UserNetwork & user):
                                                         m_data( data ),
                                                         m_background(),
                                                         m_backMenu(false),
                                                         m_back(),
                                                         m_users(),
                                                         m_user( user ),
                                                         m_request_get( HttpNetwork::path,
                                                                        sf::Http::Request::Get ),
                                                         m_request_delete( HttpNetwork::path + "/" + m_user.getId(),
                                                                           sf::Http::Request::Delete)
{

}

void ShowUsersDataBase::Init()
{
    sf::Vector2u textureSize, windowSize;
    windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)windowSize.x / textureSize.x,
                          (float)windowSize.y / textureSize.y);

    m_back.setTexture(Pictures::instance().getTexture(Pictures::back));

    m_title.setFont(Fonts::instance().getFont());
    m_title.setString("Online Drivers");
    m_title.setFillColor(sf::Color(76, 0, 153));
    m_title.setCharacterSize(100);
    m_title.setPosition((windowSize.x / 2) - 500, 100);

    getUsers();
    buildList( windowSize );
}

void ShowUsersDataBase::HandleEvent(const sf::Event & event)
{
    if(sf::Event::MouseButtonPressed == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y});

        if (m_back.getGlobalBounds().contains(location))
            m_backMenu = !m_backMenu;

        else
        {
            for( size_t i{ 0 }; i < m_users_rectangle.size(); i++ )
            {
                auto rec = m_users_rectangle[ i ];
                if( rec.first.getGlobalBounds().contains(location))
                    std::cout << m_users.at( i ).getId() << " " << m_users.at( i ).getName() << std::endl;
            }
        }
    }
}

void ShowUsersDataBase::Update(float dt)
{
    if (m_backMenu)
    {
        sf::Http::Response response = m_data->http.sendRequest(m_request_delete);
        if( response.getStatus() == sf::Http::Response::Ok )
        {
            m_data->stateStack.RemoveState();
            m_backMenu = false;
        }
    }
}

void ShowUsersDataBase::Draw()
{
    sf::RenderWindow& window = *m_data->window;

    window.draw(m_background);
    window.draw(m_back);
    window.draw(m_title);

    for( auto & rec : m_users_rectangle )
        window.draw( rec.first );

    for( auto& txt: m_list_text )
        window.draw( txt );

    for( auto & spt : m_list_sprites )
        window.draw( spt );
}

// private functions
void ShowUsersDataBase::centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}

void ShowUsersDataBase::getUsers()
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

void ShowUsersDataBase::buildVecUsers(boost::property_tree::ptree const& pt)
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
        std::stringstream ss(values[3]);
        unsigned int game = 0;
        ss >> game;
        user.updateInGame(game);
        m_users.emplace_back( user );
    }
}

void ShowUsersDataBase::buildList( const sf::Vector2u& windowSize )
{
    size_t i = 0;

    for( auto itr = m_users.begin(); itr != m_users.end(); itr++, i++ )
    {
        sf::RectangleShape rectangle;
        sf::Text text;
        sf::Sprite sprite;

        text.setFont(Fonts::instance().getFont());
        text.setFillColor(sf::Color(76, 0, 153));
        text.setCharacterSize(70);
        text.setStyle(sf::Text::Bold);
        text.setString( (*itr).getName() );
        text.setPosition(sf::Vector2f((windowSize.x / 2.5) - 100,
                                      (windowSize.y / 3) + (i * 100)));
        m_list_text.push_back(text);
        sprite.setTexture(Pictures::instance().getTexture(itr->getSprite()));
        sprite.setTextureRect((sf::Rect(95, 0, 33,30 )));
        sprite.scale(3, 3);
        sprite.setPosition(sf::Vector2f((windowSize.x / text.getPosition().x) + 1200,
                                        (windowSize.y / 3 ) + (i * 100)));
        m_list_sprites.push_back(sprite);

        rectangle.setSize(sf::Vector2f{900, 90});
        rectangle.setFillColor(sf::Color(0, 0, 0, 80));
        rectangle.setPosition(sf::Vector2f((windowSize.x / 3) - 150,
                                           (windowSize.y / 3) + (i * 100)));

        if( itr->getInGame() == 1 )
        {
            rectangle.setOutlineColor(sf::Color::Red);
            rectangle.setOutlineThickness(5);
            m_users_rectangle.push_back( pair( rectangle, false ) );
        }
        else
        {
            rectangle.setOutlineColor(sf::Color::White);
            rectangle.setOutlineThickness(5);
            m_users_rectangle.push_back( pair( rectangle, true ) );
        }

    }
}