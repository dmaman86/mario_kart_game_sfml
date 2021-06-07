#include "HostState.h"
#include "Pictures.h"
#include "Fonts.h"
#include <iostream>


HostState::HostState(MarioKart::GameDataRef & data): m_data( data ),
                                                     m_background(),
                                                     m_backMenu(false),
                                                     m_back(),
                                                     m_createPressed(false),
                                                     m_maps(),
                                                     m_textures(),
                                                     m_nextState(false),
                                                     m_request_put(),
                                                     m_request_post(),
                                                     m_effectTime(0.0f)
{

}

void HostState::Init()
{
    sf::Vector2u textureSize;
    m_windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)m_windowSize.x / textureSize.x,
                          (float)m_windowSize.y / textureSize.y);

    m_back.setTexture(Pictures::instance().getTexture(Pictures::back));
    m_title.setFont(Fonts::instance().getFont());
    m_title.setString("Select Map");
    m_title.setFillColor(sf::Color(76, 0, 153));
    m_title.setCharacterSize(100);
    m_title.setPosition((m_windowSize.x / 2) - 500, 100);

    m_createGame.setFont(Fonts::instance().getFont());
    m_createGame.setString("Press Enter to Save");
    m_createGame.setFillColor(sf::Color(76, 0, 153));
    m_createGame.setCharacterSize(60);
    m_createGame.setOrigin(m_createGame.getLocalBounds().width / 2,
                           m_createGame.getLocalBounds().height / 2);
    m_createGame.setPosition(sf::Vector2f(m_windowSize.x * 0.5f,
                                    (m_windowSize.y / 2) + (5 * 100)));
    m_createGame.setOutlineColor(sf::Color::White);
    m_createGame.setOutlineThickness(5.f);
    initVectorMaps();
}

void HostState::initVectorMaps()
{
    for( size_t i{ 0 }; i < 3; i++ )
    {
        auto tex = sf::Texture();
        tex.loadFromImage(Pictures::instance().getMapTex(Pictures::mario_circuit_2));
        m_textures.emplace_back(tex);
    }
    for(size_t i{ 0 }, j{ 0 }; i < 3; i++, j+=5 )
    {
        auto rectangle = new sf::RectangleShape();
        rectangle->setSize(sf::Vector2f(300, 300));
        rectangle->setTexture(&m_textures[ i ]);
        rectangle->setPosition(300 + ( j * 80 ), (rectangle->getGlobalBounds().height / 2) + 100);
        m_maps.emplace_back(Pictures::mario_circuit_2, std::pair(*rectangle, false));
    }
}

void HostState::HandleEvent(const sf::Event & event)
{
    if(sf::Event::MouseButtonPressed == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y});

        if (m_back.getGlobalBounds().contains(location))
            m_backMenu = !m_backMenu;
        else
        {
            for( auto & map : m_maps )
            {
                if(map.second.first.getGlobalBounds().contains(location))
                {
                    m_data->user.setMapGame(map.first);
                    map.second.second = !map.second.second;
                    break;
                }
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if(m_createPressed && m_data->user.getId().size() > 0 )
            m_nextState = updateUser();
        else if(m_createPressed && m_data->user.getId().size() == 0)
            m_nextState = createUser();
    }
}

void HostState::Update(float dt)
{
    for( auto & map : m_maps )
    {
        if(map.second.second)
            m_createPressed = true;
    }
    if (m_backMenu)
    {
        m_data->stateStack.RemoveState();
        m_backMenu = false;
    }
    if(m_createPressed)
    {
        m_effectTime += (float)dt;
        if(m_effectTime >= 0.5f)
        {
            m_createPressed = !m_createPressed;
            m_effectTime = 0.0f;
        }
    }
    if(m_nextState)
        std::cout << "got to wait to user\n";
}

void HostState::Draw()
{
    sf::RenderWindow& window = *m_data->window;

    window.draw(m_background);
    window.draw(m_back);
    window.draw(m_title);

    for(auto map : m_maps)
        window.draw(map.second.first);

    if(m_createPressed)
        window.draw(m_createGame);
}

void HostState::centerOrigin(sf::Text & text)
{

}

bool HostState::createUser()
{
    m_request_post.setMethod( sf::Http::Request::Post );
    m_request_post.setUri( HttpNetwork::path_user );
    std::ostringstream stream;
    std::stringstream ss;
    stream << "name=" << m_data->user.getName() << "&sprite=" << m_data->user.getSprite()
           << "&host=" << m_data->user.getIfHost() << "&map=" << m_data->user.getMapGame();
    m_request_post.setBody( stream.str() );

    sf::Http::Response response = m_data->http.sendRequest( m_request_post );

    if( response.getStatus() != sf::Http::Response::Created )
        return false;
    ss << response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);
    m_data->user.setId( pt.get<std::string>("id") );
    return true;
}

bool HostState::updateUser()
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
        return false;
    return true;
}