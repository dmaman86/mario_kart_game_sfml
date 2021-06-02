#pragma once

#include <string>

class UserNetwork
{
public:
    UserNetwork(std::string, std::string, std::string, std::string);
    ~UserNetwork() = default;

    void setId( std::string& );
    const std::string& getId();
    const std::string& getName(){ return m_name; }
    void setName( std::string& );
    void updatePosition(float, float);
    void setSprite( std::string& );
    const std::string& getSprite(){ return m_sprite; }
    const std::string& getLevel(){ return m_level; }

private:
    std::string m_name;
    std::string m_id;
    float m_positionX;
    float m_positionY;
    std::string m_sprite;
    std::string m_level;
};