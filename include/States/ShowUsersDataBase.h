#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>

#include "State.h"
#include "MarioKart.h"
#include "Macros.h"
#include "User.h"
#include "Button.h"

class ShowUsersDataBase : public State
{
public:
    // constructor & destructor
    ShowUsersDataBase(MarioKart::GameDataRef&);
    ~ShowUsersDataBase() = default;
    // virtual functions
    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(const float) override;
    void Draw() override;
    //return to this state
    void Resume() override;
private:
    // privates members
    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;
    sf::Sprite m_back;
    sf::Text m_title;
    sf::Vector2u m_windowSize;

    bool m_validConnection;
    bool m_backMenu;
    bool m_selectedUser;
    std::vector<User> m_users;
    float m_time_refresh;

    using ListUsers = std::vector< Button >;
    ListUsers m_users_rectangle;
    std::vector< sf::Text > m_list_text;
    std::vector< sf::Sprite > m_list_sprites;

    std::thread m_thread_get_users;
    std::mutex m_mutex;
    bool m_get_users;

    // private functions
    void centerOrigin(sf::Text&);
    void buildList( const sf::Vector2u& );
    void finishThread();
    void deleteUser(const std::string&);
};
