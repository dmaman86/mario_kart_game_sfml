#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "State.h"
#include "MarioKart.h"
#include "Macros.h"
#include "User.h"
#include "Button.h"

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

    bool m_validConnection;
    bool m_backMenu;
    bool m_selectedUser;
    std::vector<User> m_users;

    using ListUsers = std::vector< Button >;
    ListUsers m_users_rectangle;
    std::vector< sf::Text > m_list_text;
    std::vector< sf::Sprite > m_list_sprites;

    void centerOrigin(sf::Text&);
    void buildList( const sf::Vector2u& );
};
