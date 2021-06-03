#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "State.h"
#include "MarioKart.h"
#include "UserNetwork.h"

#include <thread>
#include <chrono>
#include <SFML/Network.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <vector>

namespace pt = boost::property_tree;


/* Test state to test server */
class TestState : public State
{
public:
    TestState( MarioKart::GameDataRef );
    ~TestState() = default;

    void Init() override;
    void HandleEvent( const sf::Event& ) override;
    void Update( float ) override;
    void Draw() override;


private:
    MarioKart::GameDataRef m_data;
    sf::TcpSocket socket;
    sf::Packet last_packet;
    std::vector<UserNetwork> m_users;
    std::vector< sf::Text > m_list;
    sf::Sprite m_BackgroundSprite;
    sf::Text m_title;
    sf::Http::Request m_request_get;
    sf::Http::Request m_request_post;
    bool m_validConnection;
    UserNetwork m_user;

    void centerOrigin(sf::Text&);
    void buildVecUsers(boost::property_tree::ptree const&);
    void saveUser();
    void getUsers();
    void buildList( const sf::Vector2u& );
};
