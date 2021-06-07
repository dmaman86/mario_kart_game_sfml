#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cmath>
#include <vector>

#include "State.h"
#include "MarioKart.h"
#include "Macros.h"
#include "UserNetwork.h"

namespace pt = boost::property_tree;

class ShowUsersDataBase : public State
{
public:
    ShowUsersDataBase(MarioKart::GameDataRef&);
    ~ShowUsersDataBase() = default;

    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
private:
    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;
    sf::Sprite m_back;
    sf::Text m_title;
    sf::Vector2u m_windowSize;

    sf::Http::Request m_request_get;
    sf::Http::Request m_request_delete;
    bool m_validConnection;
    bool m_backMenu;
    std::vector<UserNetwork> m_users;

    typedef std::pair< sf::RectangleShape, bool > pair;
    using ListUsers = std::vector< pair >;
    ListUsers m_users_rectangle;
    std::vector< sf::Text > m_list_text;
    std::vector< sf::Sprite > m_list_sprites;

    void centerOrigin(sf::Text&);
    void buildVecUsers(boost::property_tree::ptree const&);
    void getUsers();
    void buildList( const sf::Vector2u& );
};
