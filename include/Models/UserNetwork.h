#pragma once

#include <string>
#include "SFML/Graphics.hpp"

class UserNetwork
{
public:
    UserNetwork(std::string id, std::string name, std::string sprite);
    ~UserNetwork() = default;

    void setId( std::string );
    const std::string& getId();
    const std::string& getName(){ return m_name; }
    void setName( std::string& );
    void updatePosition();
    const sf::Vector2f& getPosition();
    void setSprite( std::string& );
    const std::string& getSprite(){ return m_sprite; }

private:
    std::string m_id;
    std::string m_name;
    std::string m_sprite;
    sf::Vector2f m_position;
    float m_angle;
    float m_speed;
    bool m_inGame = false;
};